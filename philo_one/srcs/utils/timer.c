/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:00 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/11 08:09:02 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		update_current_time(t_data *data)
{
	static unsigned long long	origin_time;
	static unsigned long long	current_time;
	static struct timeval		time;

	usleep(10);
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (origin_time == 0)
		origin_time = current_time;
	data->current_clock = (current_time - origin_time);
}

unsigned long	get_current_time(void)
{
	return (get_data(GET)->current_clock);
}

void			*clock_routine(__attribute__((unused))void *arg)
{
	t_data						*data;

	data = get_data(GET);
	while (data->first_death_report == false)
		update_current_time(data);
	pthread_exit(NULL);
}
