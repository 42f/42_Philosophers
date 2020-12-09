/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 15:29:39 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static t_state		wake_up_action_handler(t_data *data, const int philo_id)
{
	put_status(data, philo_id, MESSAGE_IS_THINKING);
	return (thinking_state);
}

static t_state		take_forks_action_handler(t_data *data, const int philo_id)
{
	acquire_forks(data);
	if (data->death_report_flag == true)
		return (done_eating_state);
	put_status(data, philo_id, MESSAGE_HAS_TAKEN_FORK);
	return (has_forks_state);
}

static t_state		drop_fork_action_handler(t_data *data, const int philo_id)
{
	drop_forks(data);
	put_status(data, philo_id, MESSAGE_IS_SLEEPING);
	usleep(data->param[T_TO_SLEEP]);
	return (sleeping_state);
}

static t_state		eat_action_handler(t_data *data, const int philo_id)
{
	data->last_meal[philo_id] = get_current_time();
	put_status(data, philo_id, MESSAGE_IS_EATING);
	data->nb_meals_eaten[philo_id]++;
	usleep(data->param[T_TO_EAT]);
	if (data->param[NB_MEALS] != UNSET
				&& data->nb_meals_eaten[philo_id] >= data->param[NB_MEALS])
		return (done_eating_state);
	return (eating_state);
}

static void		done_eating_action_handler(t_data *data, const int philo_id)
{
	data->done_report_flag[philo_id] = true;
	drop_forks(data);
}

void			*philo_state_machine(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	state = startup_state;
	data->done_report_flag[philo_id] = false;
	data->nb_meals_eaten[philo_id] = 0;
	data->last_meal[philo_id] = get_current_time();
	while(check_loop_conditions(state, data) == true)
	{
		if (state == has_forks_state)
			state = eat_action_handler(data, philo_id);
		else if (state == thinking_state || state == startup_state )
			state = take_forks_action_handler(data, philo_id);
		else if (state ==  eating_state)
			state = drop_fork_action_handler(data, philo_id);
		else if (state == sleeping_state)
			state = wake_up_action_handler(data, philo_id);
		state = check_aliveness(data, philo_id, state);
	}
	if (state == done_eating_state)
		done_eating_action_handler(data, philo_id);
	pthread_exit(NULL);
}
