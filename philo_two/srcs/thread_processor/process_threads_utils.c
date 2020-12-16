/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_threads_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 14:11:34 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			init_sem(t_data *data)
{
	data->sem_nb_philo_done = safe_sem_open(SEM_NAME_NB_PHILO_DONE, 1);
	data->sem_stdout = safe_sem_open(SEM_NAME_STDOUT, 1);
	data->sem_death_report = safe_sem_open(SEM_NAME_DEATH_REPORT, 1);
	data->sem_forks_heap = safe_sem_open(SEM_NAME_FORKS_HEAP,
														data->param[NB_PHILO]);
	data->sem_race_starter = safe_sem_open(SEM_NAME_RACE_STARTER, 1);
}

void			init_threads_arr(pthread_t **th_philo,
					pthread_t **th_monitor, int **philo_id)
{
	*philo_id = (int *)malloc_and_set(sizeof(int), 0);
	*th_philo = (pthread_t *)malloc_and_set(sizeof(pthread_t), 0);
	*th_monitor = (pthread_t *)malloc_and_set(sizeof(pthread_t), 0);
	if (*philo_id == NULL || *th_philo == NULL || *th_monitor == NULL)
	{
		failed_init_arrays(*th_philo, *th_monitor, *philo_id);
		exit_routine(CODE_ERR_MALLOC);
	}
}

void			destroy_sem(t_data *data)
{
	safe_sem_close(data->sem_race_starter, SEM_NAME_RACE_STARTER);
	safe_sem_close(data->sem_nb_philo_done, SEM_NAME_NB_PHILO_DONE);
	safe_sem_close(data->sem_stdout, SEM_NAME_STDOUT);
	safe_sem_close(data->sem_death_report, SEM_NAME_DEATH_REPORT);
	safe_sem_close(data->sem_forks_heap, SEM_NAME_FORKS_HEAP);
}

void			failed_init_arrays(pthread_t *th_philo,
					pthread_t *th_monitor, int *philo_id)
{
	safe_free(th_philo);
	safe_free(th_monitor);
	safe_free(philo_id);
}
