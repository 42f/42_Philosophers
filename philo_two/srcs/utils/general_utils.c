/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:03 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 09:39:13 by bvalette         ###   ########.fr       */
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

void			*malloc_and_set(size_t size, int set_value)
{
	void			*new_mem;
	size_t			nb_philo;

	new_mem = NULL;
	nb_philo = (size_t)get_data(GET)->param[NB_PHILO];
	new_mem = malloc(size * (nb_philo + 1));
	if (new_mem == NULL)
		return (NULL);
	return (memset(new_mem, set_value, size * (nb_philo + 1)));
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

unsigned long	get_death_time(t_data *data, int philo_id)
{
	unsigned long	death_time;

	death_time = data->first_death_report_timestamp;
	if (death_time - data->last_meal[philo_id] - data->param[T_TO_DIE] > 10)
		return (data->last_meal[philo_id] + data->param[T_TO_DIE] + 1);
	else
		return (data->first_death_report_timestamp);
}

void			free_data_struct_content(t_data *data)
{
	safe_free(data->last_meal);
	safe_free(data->nb_meals_eaten);
	safe_free(data->done_report_flag);
	safe_free(data->philo_state);
	safe_free(data->philo_state_time_stamp);
}
