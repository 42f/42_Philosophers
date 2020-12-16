/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 16:02:18 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		exit_status(int *wstatus)
{
	if (wstatus != NULL && WIFEXITED(wstatus) == true)
		return (WEXITSTATUS(wstatus));
	else
		return (0);
}

static void		waiter(void)
{
	bool	is_first_death;
	int		*wstatus;

	is_first_death = true;
	while (waitpid(ANY_CHILD, wstatus, NO_OPTIONS) != FAILURE)
	{
		if (exit_status(wstatus) == CHILD_IS_DEAD && is_first_death == true)
		{
			kill(EVERY_CHILDREN, SIGTERM);
																// signal term or ?...
			is_first_death = false;
		}
	}
}

static void		fork_loop(t_data *data)
{
	int		philo_id;
	pid_t	pid;

	pid = 0;
	philo_id = 1;
	while (philo_id <= data->param[NB_PHILO])
	{
		pid = fork();
		if (pid == CHILD_PROCESS_PID)
			child_process(data, philo_id);
		else if (pid == FAILURE)
		{
			kill(EVERY_CHILDREN, SIGTERM);
			exit_routine(CODE_ERR_FORK);
		}
		philo_id++;
	}
}

void			process_fork(t_data *global_data)
{
	init_sem(global_data);
	sem_wait(global_data->sem_race_starter);
	fork_loop(global_data);
	sem_post(global_data->sem_race_starter);
	waiter();
	destroy_sem(global_data);
}
