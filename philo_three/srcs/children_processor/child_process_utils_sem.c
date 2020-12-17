/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils_sem.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 16:43:14 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		ft_fill(char *buffer, unsigned long n_val)
{
	while (n_val > 0)
	{
		*buffer = (n_val % 10) + '0';
		n_val /= 10;
		buffer--;
	}
}

static void		ft_itoa(unsigned long nb, char *buffer)
{
	size_t				len;
	unsigned long		nb_val;

	if (nb != 0)
	{
		len = 0;
		nb_val = nb;
		while (nb_val != 0)
		{
			nb_val = nb_val / 10;
			len++;
		}
		ft_fill(buffer + len, nb);
	}
}

static void		init_name(t_data *local_data, int philo_id)
{
	static const char	*name = SEM_NAME_DEATH_REPORT;
	int					i;

	memset(local_data->sem_death_report_name_buff, '\0', BUFF_SIZE);
	i = 0;
	while (name[i] != '\0' && i < BUFF_SIZE)
	{
		local_data->sem_death_report_name_buff[i] = name [i];
		i++;
	}
	ft_itoa(philo_id, local_data->sem_death_report_name_buff + i - 1);
}

void			init_local_semaphore(t_data *local_data, int philo_id)
{
	init_name(local_data, philo_id);
	local_data->sem_death_report = safe_sem_open(
									local_data->sem_death_report_name_buff, 1);
	if (local_data->sem_death_report == SEM_FAILED)
		exit_routine_childprocess(CODE_ERR_SEM);
}
