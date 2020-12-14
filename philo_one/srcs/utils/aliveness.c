/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliveness.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:55 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/14 18:07:06 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

bool	is_alive(t_data *data, const int philo_id)
{
	int				t_delta;
	unsigned long	time;

	// pthread_mutex_lock(&data->mutex_last_meal[philo_id]);
	time = get_current_time();
	t_delta = time - data->last_meal[philo_id];
	// if (data->first_death_report == false && t_delta > data->param[T_TO_DIE])
	// if (t_delta > data->param[T_TO_DIE])
	// {
	// 	data->philo_state_time_stamp[philo_id] = get_current_time();
	// 	dprintf(STDERR_FILENO, "%ld %d ______________DEAAAAAAAAAD !!!!\n", get_current_time(), philo_id);
	// }
 	// pthread_mutex_unlock(&data->mutex_last_meal[philo_id]);
	return (t_delta <= data->param[T_TO_DIE]);
}

t_state		check_aliveness(t_data *data, int philo_id,
													const t_state current_state, int time)
{
	t_state			ret_state;

	// pthread_mutex_lock(&data->mutex_last_meal[philo_id]);
	ret_state = current_state;
	// if (is_alive(data, philo_id) == false)
	// if (time - (int)data->last_meal[philo_id] > data->param[T_TO_DIE])
	// {
		// dprintf(STDERR_FILENO, "[[%d]] %ld %d ______________DEAAAAAAAAAD !!!!\n", time - (int)data->last_meal[philo_id], get_current_time(), philo_id);
		// dprintf(STDERR_FILENO, "%ld %d ______________WAITING for mutex\n", get_current_time(), philo_id);
	data->philo_state_time_stamp[philo_id] = time;
	pthread_mutex_lock(&data->mutex_death_report);
	if (data->first_death_report == false)
	{
		// dprintf(STDERR_FILENO, "%ld %d FLAAAAAAAAAAAAAAG\n", get_current_time(), philo_id);
		data->first_death_report = true;
		// data->philo_state_time_stamp[philo_id] = get_current_time();
		ret_state = dead_state;
	}
	else
		ret_state = current_state;
	pthread_mutex_unlock(&data->mutex_death_report);
	// }
	return (ret_state);
}
