/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:00 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/19 10:55:15 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>
#include <sys/time.h>

static unsigned long int	gettime(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) == -1)
		return (0);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void			*clock_routine(void *data_arg)
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
		// dprintf(STDERR_FILENO, "%13ld . ",data->current_clock);			// TODO: remove FOBIDDEN
		usleep(900);
	}
	return (NULL);
}
