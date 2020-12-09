/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 17:12:56 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	status_printer(t_data *data, const int philo_id, unsigned long time,
															const char *message)
{
	if (ft_putnbr(time) == FAILURE)
	{
		pthread_mutex_unlock(&data->mutex_stdout);
		exit_routine(CODE_ERR_MALLOC);
	}
	if (ft_putnbr(philo_id) == FAILURE)
	{
		pthread_mutex_unlock(&data->mutex_stdout);
		exit_routine(CODE_ERR_MALLOC);
	}
	ft_put_str_fd(STDOUT_FILENO, message);
}

void		put_death_status(t_data *data, const int philo_id)
{
	unsigned long	time;

	time = get_current_time();
	pthread_mutex_lock(&data->mutex_stdout);
	status_printer(data, philo_id, time, MESSAGE_IS_DEAD);
	pthread_mutex_unlock(&data->mutex_stdout);
}

void		put_regular_status(t_data *data, const int philo_id,
															const char *message)
{
	unsigned long	time;

	time = get_current_time();
	pthread_mutex_lock(&data->mutex_stdout);
	if (data->death_report_flag == false)
		status_printer(data, philo_id, time, message);
	pthread_mutex_unlock(&data->mutex_stdout);
}
