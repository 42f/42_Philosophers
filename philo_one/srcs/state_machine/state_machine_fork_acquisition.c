/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_fork_acquisition.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/19 11:55:17 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			get_right_philo_id(t_data *data, int philo_id)
{
	if (philo_id < data->param[NB_PHILO])
		return (philo_id + 1);
	else
		return (1);
}

static void	try_grab_left_then_right_fork(t_data *data, int right_philo_id,
																int philo_id)
{
	pthread_mutex_lock(&data->mutex_fork[philo_id]);
	data->philo_state_time_stamp[philo_id] = data->current_clock;
	put_regular_status(data, philo_id, LEN_HAS_FORK, MESSAGE_HAS_FORK);
	pthread_mutex_lock(&data->mutex_fork[right_philo_id]);
	data->philo_state_time_stamp[philo_id] = data->current_clock;
	put_regular_status(data, philo_id, LEN_HAS_FORK, MESSAGE_HAS_FORK);
	data->last_meal[philo_id] = data->philo_state_time_stamp[philo_id];
}

static void	try_grab_right_then_left_fork(t_data *data, int right_philo_id,
																int philo_id)
{
	pthread_mutex_lock(&data->mutex_fork[right_philo_id]);
	data->philo_state_time_stamp[philo_id] = data->current_clock;
	put_regular_status(data, philo_id, LEN_HAS_FORK, MESSAGE_HAS_FORK);
	pthread_mutex_lock(&data->mutex_fork[philo_id]);
	data->philo_state_time_stamp[philo_id] = data->current_clock;
	put_regular_status(data, philo_id, LEN_HAS_FORK, MESSAGE_HAS_FORK);
	data->last_meal[philo_id] = data->philo_state_time_stamp[philo_id];
}

void		acquire_forks(t_data *data, int philo_id)
{
	int				right_philo_id;

	right_philo_id = get_right_philo_id(data, philo_id);
	if (data->nb_meals_eaten[philo_id] == 0 && philo_id % 2 != 0)
	{
		usleep(1 * 1000);
		try_grab_right_then_left_fork(data, right_philo_id, philo_id);
	}
	else
		try_grab_left_then_right_fork(data, right_philo_id, philo_id);
	data->philo_state_time_stamp[philo_id] = data->last_meal[philo_id];
	pthread_mutex_lock(&data->mutex_death_report);
	put_regular_status(data, philo_id, LEN_IS_EATING, MESSAGE_EATING);
	pthread_mutex_unlock(&data->mutex_death_report);
}
