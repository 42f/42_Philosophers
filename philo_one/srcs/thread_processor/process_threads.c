/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/15 15:27:50 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void			failed_thread_creation(t_data *data)
{
	data->first_death_report = true;
	data->nb_philo_done = data->param[NB_PHILO];
	exit_routine(CODE_ERR_PTHREAD);
}

static void			thread_creation_loop(t_data *data,
			pthread_t *thread, void *(*routine)(void *), int *philo_id)
{
	int			i;

	i = 0;
	while (i < data->param[NB_PHILO])
	{
		philo_id[i] = i + 1;
		if (pthread_create(&thread[i], NULL, routine, &philo_id[i]) != 0)
			failed_thread_creation(data);
		usleep(1000);
		i++;
	}
}

static void			thread_join_loop(const t_data *data, pthread_t *thread)
{
	int			i;

	i = 0;
	while (i < data->param[NB_PHILO])
	{
		if (pthread_join(thread[i], NULL) != 0)
			ft_put_str_fd(STDERR_FILENO, "Error while trying to join thread\n");
		i++;
	}
}

void				process_philo(t_data *data)
{
	pthread_t	*th_philo;
	pthread_t	*th_monitor;
	int			*philo_id;
	pthread_t	th_clock;

	init_mutex(data);
	init_threads_arr(&th_philo, &th_monitor, &philo_id, data->param[NB_PHILO]);
	pthread_mutex_lock(&data->mutex_race_starter);
	if (pthread_create(&th_clock, NULL, clock_routine, data) != 0)
		exit_routine(CODE_ERR_PTHREAD);
	thread_creation_loop(data, th_philo, philo_state_machine, philo_id);
	thread_creation_loop(data, th_monitor, philo_monitor, philo_id);
	pthread_mutex_unlock(&data->mutex_race_starter);
	thread_join_loop(data, th_philo);
	thread_join_loop(data, th_monitor);
	pthread_join(th_clock, NULL);
	destroy_mutex(data);
	safe_free(th_philo);
	safe_free(th_monitor);
	safe_free(philo_id);
}
