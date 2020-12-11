/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:00 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/11 19:22:36 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		update_current_time(t_data *data)
{
	static unsigned long	origin_time;
	static unsigned long	current_time;
	static struct timeval	time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 10000) + (time.tv_usec / 100);
	if (origin_time == 0)
		origin_time = current_time;
	data->current_clock = (current_time - origin_time);
	dprintf(STDERR_FILENO, "TIME (%ld - %ld) %ld / %ld\n",time.tv_sec, time.tv_usec, current_time,data->current_clock);
}

unsigned long	get_current_time(void)
{
	return (get_data(GET)->current_clock);
}

void			*clock_routine(void *data_arg)
{
	t_data						*data;

	data = (t_data *)data_arg;
	while (data->first_death_report == false && data->first_done_report == false)
		update_current_time(data);
	pthread_exit(NULL);
}
