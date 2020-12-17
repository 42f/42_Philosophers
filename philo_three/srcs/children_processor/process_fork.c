/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:32:54 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 17:55:37 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		kill_all_philo(t_gdata *gdata, pid_t pid_already_dead_philo)
{
	int		philo_to_kill;
	int		pid_to_kill;

	philo_to_kill = 1;
	while (philo_to_kill <= gdata->param[NB_PHILO])
	{
		pid_to_kill = gdata->philo_pids[philo_to_kill];
		if (pid_to_kill != pid_already_dead_philo && pid_to_kill > 1)
		{
			kill(pid_to_kill, SIGTERM);
		}
		philo_to_kill++;
	}
}

static void		waiter(t_gdata *gdata)
{
	int		exit_value;
	bool	is_the_first_death;
	int		wstatus;
	pid_t	pid;

	is_the_first_death = true;
	wstatus = 0;
	while ((pid = waitpid(EVERY_CHILDREN, &wstatus, NO_OPTIONS)) != FAILURE)
	{
		exit_value = exit_status(wstatus);
		if ((exit_value == CHILD_IS_DEAD || exit_value == CHILD_FAILURE)
												&& is_the_first_death == true)
		{
			kill_all_philo(gdata, pid);
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
		{
			gdata->philo_pids[philo_id] = pid;
			philo_id++;
		}
	}
}

void			process_fork(t_gdata *global_data)
{
	int		i;

	init_philo_pids(global_data);
	init_sem(global_data);
	i = 0;
	while (i < global_data->param[NB_PHILO])
	{
		sem_wait(global_data->sem_race_starter);
		i++;
	}
	fork_loop(global_data);
	i = 0;
	while (i < global_data->param[NB_PHILO])
	{
		sem_post(global_data->sem_race_starter);
		i++;
	}
	waiter(global_data);
	safe_free(global_data->philo_pids);
	destroy_sem(global_data);
}
