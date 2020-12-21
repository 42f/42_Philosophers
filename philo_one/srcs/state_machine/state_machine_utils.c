/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/19 11:35:59 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		drop_forks(t_data *data, int philo_id)
{
	int		right_philo_id;

	right_philo_id = get_right_philo_id(data, philo_id);
	pthread_mutex_unlock(&data->mutex_fork[right_philo_id]);
	pthread_mutex_unlock(&data->mutex_fork[philo_id]);
}

void		report_nb_meals_reached_and_exit_thread(t_data *data, int philo_id)
{
	data->done_report_flag[philo_id] = true;
	pthread_mutex_lock(&data->mutex_nb_philo_done_counter);
	data->nb_philo_done++;
	pthread_mutex_unlock(&data->mutex_nb_philo_done_counter);
	pthread_exit(NULL);
}
