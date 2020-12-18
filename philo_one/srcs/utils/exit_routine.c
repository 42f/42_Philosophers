/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:55 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 09:00:00 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_free(void *mem)
{
	if (mem != NULL)
	{
		free(mem);
		mem = NULL;
	}
}

int		exit_routine(t_code_err err)
{
	t_data				*data;
	static const char	*message[NB_ERR_CODE] =
	{ ERR_MALLOC, ERR_MUTEX, ERR_PTHREAD };

	data = get_data(GET);
	if (data != NULL)
	{
		destroy_mutex(data);
		safe_free(data->last_meal);
		safe_free(data->nb_meals_eaten);
		safe_free(data->done_report_flag);
		safe_free(data->philo_fork);
		safe_free(data->philo_state_time_stamp);
		safe_free(data->mutex_fork);
	}
	if (err != CODE_ERR_NORMAL_EXIT && err >= 0 && err < NB_ERR_CODE)
		ft_put_str_fd(STDERR_FILENO, message[err]);
	return(FAILURE);
}
