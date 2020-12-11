/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/11 14:49:00 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			*philo_state_machine(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	data->last_meal[philo_id] = get_current_time();
	data->philo_state_time_stamp[philo_id] = get_current_time();
	state = startup_state;
	while (check_loop_conditions(state, data) == true)
	{
		if (state == thinking_state || state == startup_state)
			state = take_forks_and_eat_action_handler(data, philo_id);
		else if (state == finished_meal_state)
			state = sleep_action_handler(data, philo_id);
		else if (state == sleeping_state)
			state = think_action_handler(data, philo_id);
	}
	if (state == done_eating_state)
		done_eating_action_handler(data, philo_id);
	pthread_exit(NULL);
}











		// if (check_aliveness(data, philo_id, state) == dead_state)
		// 	put_death_status(data, philo_id);
