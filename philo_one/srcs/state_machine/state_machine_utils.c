/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/10 09:40:44 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	acquire_forks(t_data *data)
{
	int	forks_acquired;

	forks_acquired = 0;
	while (data->death_report_flag == false && forks_acquired < 2)
	{
		if (data->nb_available_forks >= 2)
		{
			pthread_mutex_lock(&data->mutex_forks);
			forks_acquired = 2;
			data->nb_available_forks -= 2;
			pthread_mutex_unlock(&data->mutex_forks);
		}
		else if (data->nb_available_forks == 1)
		{
			pthread_mutex_lock(&data->mutex_forks);
			forks_acquired += 1;
			data->nb_available_forks -= 1;
			pthread_mutex_unlock(&data->mutex_forks);
		}
	}
}

void	drop_forks(t_data *data)
{
	pthread_mutex_lock(&data->mutex_forks);
	data->nb_available_forks += 2;
	pthread_mutex_unlock(&data->mutex_forks);
}

bool	check_loop_conditions(const t_state state, const t_data *data)
{
	return (data->death_report_flag != true && state != done_eating_state);
}

void	update_last_meal(t_data *data, int philo_id)
{
	pthread_mutex_lock(&data->mutex_last_meal);
	data->last_meal[philo_id] = get_current_time();
	pthread_mutex_unlock(&data->mutex_last_meal);
}
