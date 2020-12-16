/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 15:48:59 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*safe_sem_open(const char *name, int sem_value)
{
	sem_t	*opened_semaphore;

	errno = 0;
	opened_semaphore = NULL;
	opened_semaphore = sem_open(name, O_CREAT | O_EXCL, 0644, sem_value);
	if (opened_semaphore == SEM_FAILED && errno == EEXIST)
	{
		sem_unlink(name);
		opened_semaphore = sem_open(name, O_CREAT | O_EXCL, 0644, sem_value);
	}
	if (opened_semaphore == SEM_FAILED)
		exit_routine(CODE_ERR_SEM);
	return (opened_semaphore);
}

void	safe_sem_close(sem_t *sem_to_close, const char* name)
{
	if (sem_to_close != NULL)
		sem_close(sem_to_close);
	sem_unlink(name);
}

void			init_sem(t_data *data)
{
	data->sem_stdout = safe_sem_open(SEM_NAME_STDOUT, 1);
	data->sem_forks_heap = safe_sem_open(SEM_NAME_FORKS_HEAP,
														data->param[NB_PHILO]);
	data->sem_race_starter = safe_sem_open(SEM_NAME_RACE_STARTER, 1);
}

void			destroy_sem(t_data *data)
{
	safe_sem_close(data->sem_race_starter, SEM_NAME_RACE_STARTER);
	safe_sem_close(data->sem_stdout, SEM_NAME_STDOUT);
	safe_sem_close(data->sem_forks_heap, SEM_NAME_FORKS_HEAP);
}
