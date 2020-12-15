/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:03 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/15 16:44:21 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_data	*get_data(t_data *mem)
{
	static t_data	*mem_backup = NULL;

	if (mem != GET)
		mem_backup = mem;
	return (mem_backup);
}

void	*malloc_and_set(size_t size, int set_value)
{
	void			*new_mem;
	size_t			nb_philo;

	nb_philo = (size_t)get_data(GET)->param[NB_PHILO];
	new_mem = malloc(size * (nb_philo + 1));
	if (new_mem == NULL)
		exit_routine(CODE_ERR_MALLOC);
	return (memset(new_mem, set_value, size * nb_philo + 1));
}

int		is_digit_only(const char *av)
{
	int		i;

	i = 0;
	while (av != NULL && av[i] != '\0')
	{
		if ((av[i] < '0' || av[i] > '9') && (av[i] != '+' || av[i] != ' '))
			return (false);
		i++;
	}
	return (true);
}

void	free_data_struct_content(t_data *data)
{
	safe_free(data->last_meal);
	safe_free(data->nb_meals_eaten);
	safe_free(data->done_report_flag);
	safe_free(data->philo_fork);
	safe_free(data->philo_state);
	safe_free(data->philo_state_time_stamp);
	safe_free(data->mutex_fork);
}
