/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 13:32:50 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		duplicate_global_data(t_data *local_data, t_gdata *global_data)
{
	int			i;

	local_data->sem_forks_heap = global_data->sem_forks_heap;
	local_data->sem_race_starter = global_data->sem_race_starter;
	local_data->sem_stdout = global_data->sem_stdout;
	i = 0;
	while (i < NB_OF_PARAM)
	{
		local_data->param[i] = global_data->param[i];
		i++;
	}
}

void			child_process(t_gdata *global_data, int philo_id)
{
	pthread_t	th_clock;
	pthread_t	th_philo;
	pthread_t	th_monitor;
	t_data		local_data;

	memset(&local_data, 0, sizeof(t_data));
	duplicate_global_data(&local_data, global_data);
	init_local_semaphore(&local_data, philo_id);
	get_data(&local_data);
	update_current_time(&local_data);
	if (pthread_create(&th_clock, NULL, clock_routine, &local_data) != 0)
		exit_routine_childprocess(CODE_ERR_PTHREAD);
	if (pthread_create(&th_monitor, NULL, philo_monitor, &philo_id) != 0)
		exit_routine_childprocess(CODE_ERR_PTHREAD);
	if (pthread_create(&th_philo, NULL, philo_state_machine, &philo_id) != 0)
		exit_routine_childprocess(CODE_ERR_PTHREAD);
	pthread_join(th_monitor, NULL);
	pthread_join(th_philo, NULL);
	pthread_join(th_clock, NULL);
	exit(0);
}
