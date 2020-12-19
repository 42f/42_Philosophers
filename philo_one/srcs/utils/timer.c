/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:00 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/19 09:11:38 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void		update_current_time(t_data *data)
// {
// 	static unsigned long		origin_time;
// 	static unsigned long		current_time;
// 	static struct timeval		time;

// 	// usleep(250);
// 	gettimeofday(&time, NULL);
// 	current_time = (unsigned long)(time.tv_sec * 1000)
// 					+ (unsigned long)(time.tv_usec / 1000);
// 	if (origin_time == 0)
// 		origin_time = current_time;
// 	data->current_clock = current_time - origin_time;
// 		dprintf(STDERR_FILENO, "%13d . ", (int)data->current_clock);			// TODO: remove FOBIDDEN
// 		dprintf(STDERR_FILENO, "%13ld _ ", data->current_clock);			// TODO: remove FOBIDDEN

static void		update_current_time(t_data *data)
{
	static struct timeval		current_time;
	static struct timeval		origin_time;
	static struct timeval		new_time;

	gettimeofday(&current_time, NULL);
	if (origin_time.tv_sec == 0)
	{
		origin_time.tv_sec = current_time.tv_sec;
		origin_time.tv_usec = current_time.tv_usec;
	}
	new_time.tv_sec = current_time.tv_sec - origin_time.tv_sec;
	new_time.tv_usec = current_time.tv_usec - origin_time.tv_usec;

	// data->current_clock = (unsigned long)(new_time.tv_sec * 1000)
	// 				+ (unsigned long)(new_time.tv_usec / 1000);
	data->current_clock = (new_time.tv_sec * 1000)
					+ (new_time.tv_usec / 1000);

// dprintf(STDERR_FILENO, "%7d . ", (int)data->current_clock);			// TODO: remove FOBIDDEN
// dprintf(STDERR_FILENO, "%7ld _ ", data->current_clock);			// TODO: remove FOBIDDEN
dprintf(STDERR_FILENO, "[%-18ld . %-6ld _ ]", (unsigned long)current_time.tv_sec, (unsigned long)current_time.tv_usec);			// TODO: remove FOBIDDEN
dprintf(STDERR_FILENO, "{%-18ld . %-6ld _ }", current_time.tv_sec * 1000, current_time.tv_usec / 1000);			// TODO: remove FOBIDDEN
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
