/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_fork_acquisition.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/11 07:55:41 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			get_right_philo_id(t_data *data, int philo_id)
{
	if (philo_id < data->param[NB_PHILO])
		return (philo_id + 1);
	else
		return (1);
}

static void	try_grab_fork(t_data *data, int target_id, int philo_id, bool *hand)
{
	if (data->individual_fork[target_id] == FORK_AVAILABLE)
	{
		pthread_mutex_lock(&data->mutex_fork[target_id]);
		if (data->individual_fork[target_id] == FORK_AVAILABLE)
		{
			data->individual_fork[target_id] = FORK_USED;
			*hand = HAND_HAS_FORK;
			put_regular_status(data, philo_id, MESSAGE_HAS_TAKEN_FORK);
		}
		pthread_mutex_unlock(&data->mutex_fork[target_id]);
	}
}

void	acquire_forks(t_data * data, int philo_id)
{
	bool		left_hand;
	bool		right_hand;
	int			right_philo_id;

	left_hand = HAND_EMPTY;
	right_hand = HAND_EMPTY;
	right_philo_id = get_right_philo_id(data, philo_id);
 	while (data->first_death_report == false
	 	&& (left_hand == HAND_EMPTY	|| right_hand == HAND_EMPTY))
	{
		try_grab_fork(data, philo_id, philo_id, &left_hand);
		try_grab_fork(data, right_philo_id, philo_id, &right_hand);
	}
}
