/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:04 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/13 10:04:27 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static bool		loop_condition(t_data *data, int philo_id, t_state state)
{
	return (state != dead_state && data->first_death_report == false
	&& data->done_report_flag[philo_id] == false);
}

void			*philo_monitor(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	pthread_mutex_lock(&data->mutex_started_threads_counter);
	data->started_threads_counter++;
	pthread_mutex_unlock(&data->mutex_started_threads_counter);
	pthread_mutex_lock(&data->mutex_race_starter);
	pthread_mutex_unlock(&data->mutex_race_starter);
	state = startup_state;
	while (loop_condition(data, philo_id, state) == true)
		state = check_aliveness(data, philo_id, state);
	if (data->done_report_flag[philo_id] == false && state == dead_state)
		put_death_status(data, philo_id);
	pthread_exit(NULL);
}
