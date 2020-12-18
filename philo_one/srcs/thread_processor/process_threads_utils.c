/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_threads_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 09:54:42 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->mutex_race_starter, NULL) != 0)
		return (cleanup_routine(CODE_ERR_MUTEX));
	if (pthread_mutex_init(&data->mutex_nb_philo_done_counter, NULL) != 0)
		return (cleanup_routine(CODE_ERR_MUTEX));
	if (pthread_mutex_init(&data->mutex_stdout, NULL) != 0)
		return (cleanup_routine(CODE_ERR_MUTEX));
	if (pthread_mutex_init(&data->mutex_death_report, NULL) != 0)
		return (cleanup_routine(CODE_ERR_MUTEX));
	i = 0;
	while (i < data->param[NB_PHILO])
	{
		if (pthread_mutex_init(&data->mutex_fork[i], NULL) != 0)
			return (cleanup_routine(CODE_ERR_MUTEX));
		i++;
	}
	return (SUCCESS);
}

int		init_threads_arr(pthread_t **th_philo,
					pthread_t **th_monitor, int **philo_id)
{
	*philo_id = (int *)malloc_and_set(sizeof(int), 0);
	*th_philo = (pthread_t *)malloc_and_set(sizeof(pthread_t), 0);
	*th_monitor = (pthread_t *)malloc_and_set(sizeof(pthread_t), 0);
	if (*philo_id == NULL || *th_philo == NULL || *th_monitor == NULL)
	{
		failed_init_arrays(*th_philo, *th_monitor, *philo_id);
		return (cleanup_routine(CODE_ERR_MALLOC));
	}
	return (SUCCESS);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->mutex_race_starter);
	pthread_mutex_destroy(&data->mutex_nb_philo_done_counter);
	pthread_mutex_destroy(&data->mutex_stdout);
	pthread_mutex_destroy(&data->mutex_death_report);
	i = 0;
	while (i < data->param[NB_PHILO])
	{
		pthread_mutex_destroy(&data->mutex_fork[i]);
		i++;
	}
}

void	failed_init_arrays(pthread_t *th_philo,
					pthread_t *th_monitor, int *philo_id)
{
	safe_free(th_philo);
	safe_free(th_monitor);
	safe_free(philo_id);
}
