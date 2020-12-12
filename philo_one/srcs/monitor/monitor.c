/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:04 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 13:05:45 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static bool		loop_condition(t_data *data, int philo_id, t_state state)
{
	return (state != dead_state && data->first_death_report == false
	&& data->done_report_flag[philo_id] == false);
}

// static void		*printer_routine(void *arg)
// {
// 	t_printer_data	*printer_data;
// 	t_data			*data;

// 	data = get_data(GET);
// 	printer_data = (t_printer_data *)arg;
// 	put_regular_status(printer_data->philo_id, printer_data->time, printer_data->message);
// 	pthread_mutex_lock(&data->mutex_active_printer_count);
// 	data->active_printer_count--;
// 	pthread_mutex_unlock(&data->mutex_active_printer_count);
// 	free(printer_data);
// 	pthread_exit(NULL);
// }

// static void		create_printer(t_data *data, int philo_id, const char *message)
// {
// 	pthread_t		printer;
// 	t_printer_data	*printer_data;

// 	printer_data = malloc(sizeof(t_printer_data));
// 	if (printer_data == NULL)
// 		exit_routine(CODE_ERR_MALLOC);
// 	printer_data->philo_id = philo_id;
// 	printer_data->time = get_current_time();
// 	printer_data->message = message;
// 	if (pthread_create(&printer, NULL, printer_routine, printer_data) != 0)
// 		exit_routine(CODE_ERR_PTHREAD);
// 	else
// 	{
// 		pthread_mutex_lock(&data->mutex_active_printer_count);
// 		data->active_printer_count++;
// 		pthread_mutex_unlock(&data->mutex_active_printer_count);
// 		pthread_detach(printer);
// 	}
// }

// static void		create_printer(t_data *data, int philo_id, const char *message)
// {
// 	put_regular_status(philo_id, data->philo_state_time_stamp[philo_id], message);
// }


void			*philo_monitor(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	state = data->philo_state[philo_id];
	state = startup_state;
	while (loop_condition(data, philo_id, state) == true)
	{
		state = check_aliveness(data, philo_id, state);
	}
	if (data->done_report_flag[philo_id] == false && state == dead_state)
		put_death_status(data, philo_id);
	pthread_exit(NULL);
}
