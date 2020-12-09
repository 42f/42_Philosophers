/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 15:31:38 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void			failed_thread_creation(int i, pthread_t *thread)
{
	while (i >= 0)
	{
		pthread_join(thread[i], NULL);
		i--;
	}
	exit_routine(CODE_ERR_PTHREAD);
}

static int			thread_creation_loop(const t_data *data,
	pthread_t *thread, void *(*start_routine) (void *), int *philo_id)
{
	int			i;

	i = 0;
	while (i < data->param[NB_PHILO])
	{
		philo_id[i] = i + 1;
		if (pthread_create(&thread[i], NULL, start_routine, &philo_id[i]) != 0)
		{
			failed_thread_creation(i, thread);
			return (FAILURE) ;
		}
		i++;
	}
	return (SUCCESS);
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

	init_mutex(data);
	init_arrays(&th_philo, &th_monitor, &philo_id, data->param[NB_PHILO]);
	thread_creation_loop(data, th_philo, philo_state_machine, philo_id);
	thread_creation_loop(data, th_monitor, philo_monitor, philo_id);
	thread_join_loop(data, th_monitor);
	thread_join_loop(data, th_philo);
	destroy_mutex(data);
	free(th_philo);
	free(th_monitor);
	free(philo_id);
}
