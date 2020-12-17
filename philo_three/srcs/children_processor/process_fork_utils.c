/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fork_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:32:54 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 17:36:32 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		exit_status(int wstatus)
{
	if (WIFEXITED(wstatus) == true)
		return (WEXITSTATUS(wstatus));
	else
		return (0);
}

void	init_philo_pids(t_gdata *gdata)
{
	size_t	malloc_len;

	malloc_len = sizeof(pid_t) * (gdata->param[NB_PHILO] + 1);
	gdata->philo_pids = malloc(malloc_len);
	if (gdata->philo_pids == NULL)
		exit_routine_mainprocess(CODE_ERR_MALLOC, gdata);
	memset(gdata->philo_pids, 0, malloc_len);
}
