/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 09:46:47 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		exit_status(int wstatus)
{
	if (WIFEXITED(wstatus) == true)
		return (WEXITSTATUS(wstatus));
	else
		return (0);
}

static void		waiter(void)
{
	bool	is_the_first_death;
	int		wstatus;

	is_the_first_death = true;
	while (waitpid(ANY_CHILD, &wstatus, NO_OPTIONS) != FAILURE)
	{
		if (exit_status(wstatus) == CHILD_IS_DEAD && is_the_first_death == true)
		{
			kill(EVERY_CHILDREN, SIGTERM);								// signal term or ?...
			is_the_first_death = false;
		}
	}
}

static void		fork_loop(t_gdata *gdata)
{
	int		philo_id;
	pid_t	pid;

	pid = 0;
	philo_id = 1;
	while (philo_id <= gdata->param[NB_PHILO])
	{
		pid = fork();
		if (pid == CHILD_PROCESS_PID)
			child_process(gdata, philo_id);
		else if (pid == FAILURE)
		{
			kill(EVERY_CHILDREN, SIGTERM);
			exit_routine_mainprocess(CODE_ERR_FORK, gdata);
		}
		else
			philo_id++;
	}
}

void			process_fork(t_gdata *global_data)
{
	init_sem(global_data);
	sem_wait(global_data->sem_race_starter);
	fork_loop(global_data);
	sem_post(global_data->sem_race_starter);
	waiter();
	destroy_sem();
}
