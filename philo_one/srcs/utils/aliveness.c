/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliveness.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:55 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 17:23:28 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

bool	is_alive(t_data *data, const int philo_id)
{
	int			t_delta;
	// unsigned long	t_last_meal;

	// t_last_meal = data->last_meal[philo_id];
	// t_delta = get_current_time() - t_last_meal;

	pthread_mutex_lock(&data->mutex_last_meal[philo_id]);
	t_delta = get_current_time() - data->last_meal[philo_id];
	if (t_delta > data->param[T_TO_DIE])
		dprintf(STDERR_FILENO, "%ld[%d] died after not eating for %d ms (last meal was %ld)\n", get_current_time(), philo_id, t_delta, data->last_meal[philo_id]);
 	pthread_mutex_unlock(&data->mutex_last_meal[philo_id]);
	return (t_delta <= data->param[T_TO_DIE]);
}

t_state		check_aliveness(t_data *data, int philo_id,
													const t_state current_state)
{
	t_state		ret_state;

	ret_state = current_state;
	if (is_alive(data, philo_id) == false)
	{
		dprintf(STDERR_FILENO, "%ld %d ______________WAITING for mutex\n", get_current_time(), philo_id);
		pthread_mutex_lock(&data->mutex_death_report);
		if (data->first_death_report == false)
		{
			dprintf(STDERR_FILENO, "%ld %d FLAAAAAAAAAAAAAAG\n", get_current_time(), philo_id);
			data->first_death_report = true;
			data->philo_state_time_stamp[philo_id] = get_current_time();
			pthread_mutex_unlock(&data->mutex_death_report);
			ret_state = dead_state;
		}
		else
		{
			pthread_mutex_unlock(&data->mutex_death_report);
			ret_state = current_state;
		}
	}
	return (ret_state);
}
