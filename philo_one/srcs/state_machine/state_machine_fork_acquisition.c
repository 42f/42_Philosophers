/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_fork_acquisition.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/14 17:58:44 by bvalette         ###   ########.fr       */
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
	bool		grabed_flag;

	grabed_flag = false;
	if (data->philo_fork[target_id] == FORK_AVAILABLE)
	{
		pthread_mutex_lock(&data->mutex_fork[target_id]);
		if (data->philo_fork[target_id] == FORK_AVAILABLE)
		{
			data->philo_fork[target_id] = FORK_USED;
			*hand = HAND_HAS_FORK;
			grabed_flag = true;
		}
		pthread_mutex_unlock(&data->mutex_fork[target_id]);
	}
	if (grabed_flag == true)
	{
		data->philo_state_time_stamp[philo_id] = get_current_time();
		put_regular_status(data, philo_id, LEN_HAS_TAKEN_FORK, MESSAGE_HAS_TAKEN_FORK);
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

	while (left_hand == HAND_EMPTY	|| right_hand == HAND_EMPTY)
	{
		if (get_current_time() % 2 == 0)
		{
			try_grab_fork(data, right_philo_id, philo_id, &right_hand);
			try_grab_fork(data, philo_id, philo_id, &left_hand);
		}
		else
		{
			try_grab_fork(data, philo_id, philo_id, &left_hand);
			try_grab_fork(data, right_philo_id, philo_id, &right_hand);
		}
	}
	// data->last_meal[philo_id] = get_current_time();
}
