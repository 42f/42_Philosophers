/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:03 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/26 14:34:10 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data			*get_data(t_data *mem)
{
	static t_data	*mem_backup = NULL;

	if (mem != GET)
		mem_backup = mem;
	return (mem_backup);
}

int				is_digit_only(const char *av)
{
	int				i;

	i = 0;
	while (av != NULL && av[i] != '\0')
	{
		if ((av[i] < '0' || av[i] > '9') && (av[i] != '+' || av[i] != ' '))
			return (false);
		i++;
	}
	return (true);
}
