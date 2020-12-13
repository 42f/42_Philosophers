/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/13 11:44:17 by bvalette         ###   ########.fr       */
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
	data->philo_state[philo_id] = startup_state;
	pthread_mutex_lock(&data->mutex_started_threads_counter);
	data->started_threads_counter++;
	pthread_mutex_unlock(&data->mutex_started_threads_counter);
	pthread_mutex_lock(&data->mutex_race_starter);
	// usleep(philo_id * 1000);
// dprintf(STDERR_FILENO, "%ld ....... %d .............%ld...............WAITING\n", get_current_time(), philo_id, data->last_meal[philo_id]);
	pthread_mutex_unlock(&data->mutex_race_starter);
// dprintf(STDERR_FILENO, "%ld ....... %d .............%ld..................GO\n", get_current_time(), philo_id, data->last_meal[philo_id]);
	state = startup_state;
	data->philo_state_time_stamp[philo_id] = get_current_time();
	data->last_meal[philo_id] = get_current_time();
	while (data->first_death_report != true && state != reached_meals_nb_state)
	{
		if (state == thinking_state || state == startup_state)
			state = take_forks_and_eat_action_handler(data, philo_id);
		else if (state == finished_meal_state)
			state = sleep_action_handler(data, philo_id);
	}
	if (state == reached_meals_nb_state)
		done_eating_action_handler(data, philo_id);
	pthread_exit(NULL);
}







		// if (check_aliveness(data, philo_id, state) == dead_state)
		// 	put_death_status(data, philo_id);
