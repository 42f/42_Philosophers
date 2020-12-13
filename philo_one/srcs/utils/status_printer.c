/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/13 10:47:27 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	put_regular_status(t_data *data, const int philo_id,
								const int message_len, const char *message)
{
	// if (data->first_death_report == true)
		// return ;
	pthread_mutex_lock(&data->mutex_stdout);
	if (data->first_death_report == false)
	{
		ft_putnbr(STDOUT_FILENO, get_current_time());
		ft_putnbr(STDOUT_FILENO, philo_id);
		ft_put_message_fd(STDOUT_FILENO, message_len, message);
	}
	pthread_mutex_unlock(&data->mutex_stdout);
}

void	put_death_status(t_data *data, const int philo_id)
{
	static bool	already_reported_flag;
// dprintf(STDERR_FILENO, "%ld %d trying to report...............................\n", get_current_time(), philo_id);
	pthread_mutex_lock(&data->mutex_stdout);
	if (already_reported_flag == false)
	{
// dprintf(STDERR_FILENO, "%ld %d ---------------------------------------FLAG\n", get_current_time(), philo_id);
		already_reported_flag = true;
		ft_putnbr(STDOUT_FILENO, data->philo_state_time_stamp[philo_id]);
		ft_putnbr(STDOUT_FILENO, philo_id);
		ft_put_message_fd(STDOUT_FILENO, LEN_IS_DEAD, MESSAGE_IS_DEAD);
	}
	pthread_mutex_unlock(&data->mutex_stdout);
}
