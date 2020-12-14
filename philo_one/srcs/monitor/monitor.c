/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:04 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/14 18:06:55 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"



void			*philo_monitor(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;
	int				time;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	pthread_mutex_lock(&data->mutex_started_threads_counter);
	data->started_threads_counter++;
	pthread_mutex_unlock(&data->mutex_started_threads_counter);
		// dprintf(STDERR_FILENO, "MONITOR %ld ....... %d .............%ld...............WAITING\n", get_current_time(), philo_id, data->last_meal[philo_id]);
	pthread_mutex_lock(&data->mutex_race_starter);
	pthread_mutex_unlock(&data->mutex_race_starter);
		// dprintf(STDERR_FILENO, "MONITOR %ld ....... %d .............%ld..................GO\n", get_current_time(), philo_id, data->last_meal[philo_id]);

	// pthread_mutex_lock(&data->mutex_started_threads_counter);
	data->started_threads_counter--;
	// pthread_mutex_unlock(&data->mutex_started_threads_counter);
	while(data->started_threads_counter != 0);

	state = startup_state;
	time = get_current_time();
	while (time - (int)data->last_meal[philo_id] <= data->param[T_TO_DIE] && data->first_death_report == false)
		time = get_current_time();
	// while (state != dead_state && data->first_death_report == false
	// && data->done_report_flag[philo_id] == false)
	state = check_aliveness(data, philo_id, state, time);
	if (data->done_report_flag[philo_id] == false && state == dead_state)
		put_death_status(data, philo_id);
	pthread_exit(NULL);
}
