/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:00 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/13 11:04:08 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		update_current_time(t_data *data)
{
	static unsigned long long	origin_time;
	static unsigned long long	current_time;
	static struct timeval		time;

 	usleep(5);
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (origin_time == 0)
		origin_time = current_time;
	current_time = current_time - origin_time;
	data->current_clock = current_time;
}

unsigned long	get_current_time(void)
{
	return (get_data(GET)->current_clock);
}

void			*clock_routine(void *data_arg)
{
	t_data						*data;

	data = (t_data *)data_arg;
	// pthread_mutex_lock(&data->mutex_race_starter);
	while (data->started_threads_counter < data->param[NB_PHILO] * 2);
	// pthread_mutex_unlock(&data->mutex_race_starter);
	while (data->first_death_report == false && data->first_done_report == false)
		update_current_time(data);
	pthread_exit(NULL);
}
