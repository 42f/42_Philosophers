/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_action_handlers.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 17:02:20 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_state		wake_up_action_handler(t_data *data, const int philo_id)
{
	put_regular_status(data, philo_id, MESSAGE_IS_THINKING);
	return (thinking_state);
}

t_state		take_forks_action_handler(t_data *data, const int philo_id)
{
	acquire_forks(data);
	if (data->death_report_flag == true)
		return (done_eating_state);
	put_regular_status(data, philo_id, MESSAGE_HAS_TAKEN_FORK);
	return (has_forks_state);
}

t_state		drop_fork_action_handler(t_data *data, const int philo_id)
{
	drop_forks(data);
	put_regular_status(data, philo_id, MESSAGE_IS_SLEEPING);
	usleep(data->param[T_TO_SLEEP]);
	return (sleeping_state);
}

t_state		eat_action_handler(t_data *data, const int philo_id)
{
	data->last_meal[philo_id] = get_current_time();
	put_regular_status(data, philo_id, MESSAGE_IS_EATING);
	data->nb_meals_eaten[philo_id]++;
	usleep(data->param[T_TO_EAT]);
	if (data->param[NB_MEALS] != UNSET
				&& data->nb_meals_eaten[philo_id] >= data->param[NB_MEALS])
		return (done_eating_state);
	return (eating_state);
}

void		done_eating_action_handler(t_data *data, const int philo_id)
{
	data->done_report_flag[philo_id] = true;
	drop_forks(data);
}
