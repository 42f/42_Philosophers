/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:54:58 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 09:55:09 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_usage(void)
{
	ft_put_str_fd(STDERR_FILENO, USAGE0);
	ft_put_str_fd(STDERR_FILENO, USAGE1);
	ft_put_str_fd(STDERR_FILENO, USAGE2);
	ft_put_str_fd(STDERR_FILENO, USAGE3);
}

static int	check_arguments(const int ac, const char **av)
{
	int		i;

	if (ac < 5 || ac > 6)
		return (FAILURE);
	i = 1;
	while (av != NULL && av[i] != NULL)
	{
		if (is_digit_only(av[i]) == false)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	init_philo_info_storage(t_data *data)
{
	data->last_meal = (unsigned long *)malloc_and_set(sizeof(unsigned long), 0);
	data->nb_meals_eaten = (int *)malloc_and_set(sizeof(int), 0);
	data->done_report_flag = (bool *)malloc_and_set(sizeof(bool), false);
	data->philo_fork = (bool *)malloc_and_set(sizeof(bool), FORK_AVAILABLE);
	data->philo_state_time_stamp =
					(unsigned long *)malloc_and_set(sizeof(unsigned long), 0);
	data->mutex_fork =
				(pthread_mutex_t *)malloc_and_set(sizeof(pthread_mutex_t), 0);
	if (data->last_meal == NULL || data->nb_meals_eaten == NULL
	|| data->done_report_flag == NULL || data->philo_fork == NULL
	|| data->philo_state_time_stamp == NULL || data->mutex_fork == NULL)
		return (cleanup_routine(CODE_ERR_MALLOC));
	else
		return (SUCCESS);
}

int			main(const int ac, const char **av)
{
	int		ret;
	t_data	data;

	get_data(&data);
	memset(&data, 0, sizeof(t_data));
	ret = check_arguments(ac, av);
	if (ret == SUCCESS)
		ret = process_arguments(&data, av);
	if (ret != SUCCESS)
	{
		put_usage();
		return (FAILURE_RETURN);
	}
	if (ret == SUCCESS && init_philo_info_storage(&data) == SUCCESS)
		return (process_philo(&data));
	return (FAILURE_RETURN);
}
