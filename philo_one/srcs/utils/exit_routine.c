/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:55 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/11 14:45:31 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	safe_free(void *mem)
{
	if (mem != NULL)
	{
		free(mem);
		mem = NULL;
	}
}

void	exit_routine(t_code_err err)
{
	t_data				*data;
	static const char	*message[NB_ERR_CODE] =
	{ ERR_MALLOC, ERR_MUTEX, ERR_PTHREAD };

	data = get_data(GET);
	if (data != NULL)
	{
		safe_free(data->last_meal);
		safe_free(data->nb_meals_eaten);
		safe_free(data->done_report_flag);
		safe_free(data->philo_fork);
		safe_free(data->mutex_fork);
		destroy_mutex(data);
	}
	if (err < NB_ERR_CODE)
		ft_put_str_fd(STDERR_FILENO, message[err]);
	exit(FAILURE_RETURN);
}
