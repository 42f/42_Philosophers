/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:58:07 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 10:55:47 by bvalette         ###   ########.fr       */
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

int		cleanup_routine(t_code_err err)
{
	t_data				*data;
	static const char	*message[NB_ERR_CODE] =
	{ ERR_MALLOC, ERR_SEM, ERR_PTHREAD };

	data = get_data(GET);
	if (data != NULL)
	{
		destroy_sem(data);
		free_data_struct_content(data);
	}
	if (err != CODE_ERR_NORMAL_EXIT && err >= 0 && err < NB_ERR_CODE)
	{
		ft_put_str_fd(STDERR_FILENO, message[err]);
		return (FAILURE);
	}
	else
		return (SUCCESS_RETURN);
}
