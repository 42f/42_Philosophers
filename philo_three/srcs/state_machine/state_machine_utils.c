/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 12:37:08 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		aquire_forks(t_data *data, int philo_id)
{
	if (data->nb_meals_eaten == 0 && philo_id % 2 != 0)
		usleep(10 * 1000);
	sem_wait(data->sem_forks_heap);
	data->philo_state_time_stamp = data->current_clock;
	put_regular_status(data, philo_id, LEN_HAS_FORK, MESSAGE_HAS_FORK);
	if (data->death_report == false && data->param[NB_PHILO] > 1)
	{
		if (data->nb_meals_eaten == 0 && philo_id % 2 != 0)
			usleep(10 * 1000);
		sem_wait(data->sem_forks_heap);
		data->philo_state_time_stamp = data->current_clock;
		put_regular_status(data, philo_id, LEN_HAS_FORK, MESSAGE_HAS_FORK);
	}
	if (data->param[NB_PHILO] == 1)
		usleep(data->param[T_TO_DIE] * 1050);
}
