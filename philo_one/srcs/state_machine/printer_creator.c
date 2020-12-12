/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 15:00:59 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 15:56:31 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


static void		*thread_printer(void *arg)
{
	t_printer_data	*printer_data;
	t_data			*data;

	data = get_data(GET);
	printer_data = (t_printer_data *)arg;
	printer_data->printer_routine(data, printer_data->philo_id,
									printer_data->time, printer_data->message);
	pthread_mutex_lock(&data->mutex_active_printer_count);
	data->active_printer_count--;
	pthread_mutex_unlock(&data->mutex_active_printer_count);
	free(printer_data);
	pthread_exit(NULL);
}

void		create_printer(t_printer printer_routine, int philo_id,
									 unsigned long time, const char *message)
{
	t_data			*data;
	pthread_t		th_printer;
	t_printer_data	*printer_data;

	printer_data = malloc(sizeof(t_printer_data));
	if (printer_data == NULL)
		exit_routine(CODE_ERR_MALLOC);
	printer_data->printer_routine = printer_routine;
	printer_data->philo_id = philo_id;
	printer_data->time = time;
	printer_data->message = message;
	if (pthread_create(&th_printer, NULL, thread_printer, printer_data) == 0)
	{
		data = get_data(GET);
		pthread_mutex_lock(&data->mutex_active_printer_count);
		data->active_printer_count++;
		pthread_mutex_unlock(&data->mutex_active_printer_count);
		pthread_detach(th_printer);
	}
	else
		exit_routine(CODE_ERR_PTHREAD);
}
