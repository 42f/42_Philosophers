/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 13:09:28 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	status_printer(t_data *data, const int philo_id, unsigned long time,
															const char *message)
{
	#ifdef DEBUG_MODE
	ft_put_str_fd(STDOUT_FILENO, ".");
	if (ft_putnbr(get_current_time()) == FAILURE)						// TODO: REMOVE
	{
		pthread_mutex_unlock(&data->mutex_stdout);
		exit_routine(CODE_ERR_MALLOC);
	}
	#endif
pthread_mutex_lock(&data->mutex_stdout);
	if (data->first_death_report == false)
	{
		#ifdef DEBUG_MODE
		ft_put_str_fd(STDOUT_FILENO, ".");
		if (ft_putnbr(get_current_time()) == FAILURE)						// TODO: REMOVE
		{
			pthread_mutex_unlock(&data->mutex_stdout);
			exit_routine(CODE_ERR_MALLOC);
		}
		#endif
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
	pthread_mutex_unlock(&data->mutex_stdout);
}

static void	death_printer(t_data *data, const int philo_id, unsigned long time,
															const char *message)
{
	#ifdef DEBUG_MODE
	ft_put_str_fd(STDOUT_FILENO, ".");
	if (ft_putnbr(get_current_time()) == FAILURE)						// TODO: REMOVE
	{
		pthread_mutex_unlock(&data->mutex_stdout);
		exit_routine(CODE_ERR_MALLOC);
	}
	#endif
	#ifdef DEBUG_MODE
	ft_put_str_fd(STDOUT_FILENO, ".");
	if (ft_putnbr(get_current_time()) == FAILURE)						// TODO: REMOVE
	{
		pthread_mutex_unlock(&data->mutex_stdout);
		exit_routine(CODE_ERR_MALLOC);
	}
	#endif
	(void)data;
	if (ft_putnbr(time) == FAILURE)
		exit_routine(CODE_ERR_MALLOC);
	if (ft_putnbr(philo_id) == FAILURE)
		exit_routine(CODE_ERR_MALLOC);
	ft_put_str_fd(STDOUT_FILENO, message);
}

void		put_regular_status(const int philo_id,
											const int time, const char *message)
{
	t_data			*data;

	data = get_data(GET);
	status_printer(data, philo_id, time, message);
}

void		put_death_status(t_data *data, const int philo_id)
{
	unsigned long	time;

	time = data->philo_state_time_stamp[philo_id];
	// pthread_mutex_lock(&data->mutex_stdout);
	death_printer(data, philo_id, time, MESSAGE_IS_DEAD);
	// pthread_mutex_unlock(&data->mutex_stdout);
dprintf(STDERR_FILENO, "last meal real %ld\n", data->last_meal[philo_id]);
}
