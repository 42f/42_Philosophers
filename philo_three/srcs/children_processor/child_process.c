/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 15:54:35 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			child_process(t_data *global_data, int philo_id)
{
	t_local_data	local_data;

	get_data(&local_data);
	if (pthread_create(&th_clock, NULL, clock_routine, data) != 0)
		exit_routine(CODE_ERR_PTHREAD);
	thread_creation_loop(data, th_philo, philo_state_machine, philo_id);
	thread_creation_loop(data, th_monitor, philo_monitor, philo_id);
	sem_post(data->sem_race_starter);
	thread_join_loop(data, th_philo);
	thread_join_loop(data, th_monitor);
	pthread_join(th_clock, NULL);
}
