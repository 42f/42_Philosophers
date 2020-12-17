/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 15:47:19 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_regular_status(t_data *data, const int philo_id,
								const int message_len, const char *message)
{
	sem_wait(data->sem_stdout);
	if (data->death_report == false)
	{
		ft_putnbr(STDOUT_FILENO, data->philo_state_time_stamp);
		ft_putnbr(STDOUT_FILENO, (unsigned long)philo_id);
		ft_put_message_fd(STDOUT_FILENO, (size_t)message_len, message);
	}
	sem_post(data->sem_stdout);
}
void		put_regular_status(t_data *data, const int philo_id,
								const int message_len, const char *message)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		print_regular_status(data, philo_id, message_len, message);
		exit (0);
	}
	else if (pid == FAILURE)
		print_regular_status(data, philo_id, message_len, message);
	else
		return ;
}

void		put_death_status(t_data *data, const int philo_id)
{
	ft_putnbr(STDOUT_FILENO, get_death_time(data));
	ft_putnbr(STDOUT_FILENO, (unsigned long)philo_id);
	ft_put_message_fd(STDOUT_FILENO, LEN_IS_DEAD, MESSAGE_DEAD);
}
