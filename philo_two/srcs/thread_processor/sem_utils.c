/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 14:09:53 by bvalette         ###   ########.fr       */
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
