/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:55 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 15:16:49 by bvalette         ###   ########.fr       */
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

void	exit_routine(t_code_err err)
{
	t_data				*data;
	static const char	*message[NB_ERR_CODE] =
	{ ERR_MALLOC, ERR_FORK, ERR_SEM, ERR_PTHREAD };

	data = get_data(GET);
	if (data != NULL)
	{
		free_data_struct_content(data);
		destroy_sem(data);
	}
	if (err < NB_ERR_CODE)
		ft_put_str_fd(STDERR_FILENO, message[err]);
	exit(FAILURE_RETURN);
}
