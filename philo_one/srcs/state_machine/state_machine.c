/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 17:09:25 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		init_data(t_data *data, int philo_id)
{
	data->done_report_flag[philo_id] = false;
	data->nb_meals_eaten[philo_id] = 0;
	data->last_meal[philo_id] = get_current_time();
}

void			*philo_state_machine(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	init_data(data, philo_id);
	state = startup_state;
	while (check_loop_conditions(state, data) == true)
	{
		if (state == has_forks_state)
			state = eat_action_handler(data, philo_id);
		else if (state == thinking_state || state == startup_state)
			state = take_forks_action_handler(data, philo_id);
		else if (state == eating_state)
			state = drop_fork_action_handler(data, philo_id);
		else if (state == sleeping_state)
			state = wake_up_action_handler(data, philo_id);
		if (check_aliveness(data, philo_id, state) == dead_state)
			put_death_status(data, philo_id);
	}
	if (state == done_eating_state)
		done_eating_action_handler(data, philo_id);
	pthread_exit(NULL);
}
