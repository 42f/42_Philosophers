/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/15 17:04:00 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_regular_status(t_data *data, const int philo_id,
								const int message_len, const char *message)
{
	pthread_mutex_lock(&data->mutex_stdout);
	if (data->first_death_report == false)
	{
		ft_putnbr(STDOUT_FILENO, data->philo_state_time_stamp[philo_id]);
		ft_putnbr(STDOUT_FILENO, (unsigned long)philo_id);
		ft_put_message_fd(STDOUT_FILENO, (size_t)message_len, message);
	}
	pthread_mutex_unlock(&data->mutex_stdout);
}

void	put_death_status(t_data *data, const int philo_id)
{
	static bool	already_reported_flag;

	if (already_reported_flag == false)
	{
		pthread_mutex_lock(&data->mutex_stdout);
		if (already_reported_flag == false)
		{
			already_reported_flag = true;
			ft_putnbr(STDOUT_FILENO, data->first_death_report_timestamp);
			ft_putnbr(STDOUT_FILENO, (unsigned long)philo_id);
			ft_put_message_fd(STDOUT_FILENO, LEN_IS_DEAD, MESSAGE_IS_DEAD);
		}
		pthread_mutex_unlock(&data->mutex_stdout);
	}
}
