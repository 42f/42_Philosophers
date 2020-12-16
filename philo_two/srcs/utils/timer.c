/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:00 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 13:46:29 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		update_current_time(t_data *data)
{
	static unsigned long		origin_time;
	static unsigned long		current_time;
	static struct timeval		time;

	usleep(250);
	gettimeofday(&time, NULL);
	current_time = (unsigned long)(time.tv_sec * 1000)
					+ (unsigned long)(time.tv_usec / 1000);
	if (origin_time == 0)
		origin_time = current_time;
	data->current_clock = current_time - origin_time;
}

void			*clock_routine(void *data_arg)
{
	t_data						*data;
	int							nb_philo;

	data = (t_data *)data_arg;
	nb_philo = data->param[NB_PHILO];
	while (data->nb_philo_done < nb_philo)
		update_current_time(data);
	return (NULL);
}
