/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 17:57:10 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	put_regular_status(t_data *data, const int philo_id, unsigned long time,
															const char *message)
{
	if (data->first_death_report == true)
		return ;
	pthread_mutex_lock(&data->mutex_stdout);
	if (data->first_death_report == false)
	{
		(void)time;
		if (ft_putnbr(STDOUT_FILENO, get_current_time()) == FAILURE)
		{
			pthread_mutex_unlock(&data->mutex_stdout);
			exit_routine(CODE_ERR_MALLOC);
		}
		if (ft_putnbr(STDOUT_FILENO, philo_id) == FAILURE)
		{
			pthread_mutex_unlock(&data->mutex_stdout);
			exit_routine(CODE_ERR_MALLOC);
		}
		ft_put_str_fd(STDOUT_FILENO, message);
	}
	pthread_mutex_unlock(&data->mutex_stdout);
}

void	put_death_status(t_data *data, const int philo_id, unsigned long time,
															const char *message)
{
	static bool	already_reported_flag;
	pthread_mutex_lock(&data->mutex_stdout);
	if (already_reported_flag == false)
	{
		already_reported_flag = true;
		if (ft_putnbr(STDOUT_FILENO, time) == FAILURE)
			exit_routine(CODE_ERR_MALLOC);
		if (ft_putnbr(STDOUT_FILENO, philo_id) == FAILURE)
			exit_routine(CODE_ERR_MALLOC);
		ft_put_str_fd(STDOUT_FILENO, message);
	}
	pthread_mutex_unlock(&data->mutex_stdout);
}
