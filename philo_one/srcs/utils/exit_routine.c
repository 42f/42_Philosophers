/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:55 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 14:55:51 by bvalette         ###   ########.fr       */
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
	t_data	*data;

	data = get_data(GET);
	if (data != NULL)
	{
		safe_free(data->last_meal);
		safe_free(data->nb_meals_eaten);
		safe_free(data->done_report_flag);
		destroy_mutex(data);
	}
	if (err == CODE_ERR_MALLOC)
		ft_put_str_fd(STDERR_FILENO, ERR_MALLOC);
	else if (err == CODE_ERR_PTHREAD)
		ft_put_str_fd(STDERR_FILENO, ERR_PTHREAD);
	exit(FAILURE_RETURN);
}
