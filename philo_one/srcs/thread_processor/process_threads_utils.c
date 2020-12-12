/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_threads_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 19:11:02 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->mutex_race_starter, NULL) != 0)
		exit_routine(CODE_ERR_MUTEX);
	if (pthread_mutex_init(&data->mutex_stdout, NULL) != 0)
		exit_routine(CODE_ERR_MUTEX);
	if (pthread_mutex_init(&data->mutex_death_report, NULL) != 0)
		exit_routine(CODE_ERR_MUTEX);
	i = 0;
	while (i < data->param[NB_PHILO])
	{
		if (pthread_mutex_init(&data->mutex_fork[i], NULL) != 0)
			exit_routine(CODE_ERR_MUTEX);
		if (pthread_mutex_init(&data->mutex_last_meal[i], NULL) != 0)
			exit_routine(CODE_ERR_MUTEX);
		i++;
	}
}

void			init_threads_arr(pthread_t **th_philo,
					pthread_t **th_monitor, int **philo_id, size_t nb_philo)
{
	nb_philo += 1;
	*philo_id = (int *)malloc(nb_philo * sizeof(int));
	*th_philo = (pthread_t *)malloc(nb_philo * sizeof(pthread_t));
	*th_monitor = (pthread_t *)malloc(nb_philo * sizeof(pthread_t));
	if (*philo_id == NULL || *th_philo == NULL || *th_monitor == NULL)
	{
		failed_init_arrays(*th_philo, *th_monitor, *philo_id);
		exit_routine(CODE_ERR_MALLOC);
	}
}

void			destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->mutex_race_starter);
	pthread_mutex_destroy(&data->mutex_stdout);
	pthread_mutex_destroy(&data->mutex_death_report);
	i = 0;
	while (i < data->param[NB_PHILO])
	{
		pthread_mutex_destroy(&data->mutex_fork[i]);
		pthread_mutex_destroy(&data->mutex_fork[i]);
		i++;
	}
}

void			failed_init_arrays(pthread_t *th_philo,
					pthread_t *th_monitor, int *philo_id)
{
	safe_free(th_philo);
	safe_free(th_monitor);
	safe_free(philo_id);
}
