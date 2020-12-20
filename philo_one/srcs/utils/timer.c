/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:00 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/19 11:40:20 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>
#include <sys/time.h>

static unsigned long	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void					*clock_routine(void *data_arg)
{
	t_data						*data;
	int							nb_philo;
	unsigned long int			start;

	data = (t_data *)data_arg;
	nb_philo = data->param[NB_PHILO];
	start = gettime();
	while (data->nb_philo_done < nb_philo)
	{
		data->current_clock = gettime() - start;
		usleep(250);
	}
	return (NULL);
}
