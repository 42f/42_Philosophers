/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 13:21:25 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		drop_forks(t_data *data, int philo_id)
{
	int		right_side_philo_id;

	right_side_philo_id = get_right_philo_id(data, philo_id);
	data->philo_fork[philo_id] = FORK_AVAILABLE;
	data->philo_fork[right_side_philo_id] = FORK_AVAILABLE;
}

// void	update_last_meal(t_data *data, int philo_id)
// {
// 	(void)data;
// 	(void)philo_id;
// 	// pthread_mutex_lock(&data->mutex_last_meal);
// 	// data->last_meal[philo_id] = get_current_time();
// 	// pthread_mutex_unlock(&data->mutex_last_meal);
// }
