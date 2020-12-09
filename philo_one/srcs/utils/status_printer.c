/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 15:06:32 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			put_status(t_data *data, const int philo_id, const char *message)
{
	unsigned long	time;

	time = get_current_time();
	pthread_mutex_lock(&data->mutex_stdout);
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
	pthread_mutex_unlock(&data->mutex_stdout);
}
