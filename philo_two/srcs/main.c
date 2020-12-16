/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:07 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 09:38:12 by bvalette         ###   ########.fr       */
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

static void	init_philo_info_storage(t_data *data)
{
	data->last_meal = (unsigned long *)malloc_and_set(sizeof(unsigned long), 0);
	data->nb_meals_eaten = (int *)malloc_and_set(sizeof(int), 0);
	data->done_report_flag = (bool *)malloc_and_set(sizeof(bool), false);
	// data->philo_fork = (bool *)malloc_and_set(sizeof(bool), FORK_AVAILABLE);
	data->philo_state_time_stamp =
					(unsigned long *)malloc_and_set(sizeof(unsigned long), 0);
	// data->sem_fork =
				// (pthread_mutex_t *)malloc_and_set(sizeof(pthread_mutex_t), 0);
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
	if (ret == SUCCESS)
	{
		init_philo_info_storage(&data);
		process_philo(&data);
		free_data_struct_content(&data);
	}
	else
	{
		put_usage();
		return (FAILURE_RETURN);
	}
	return (SUCCESS_RETURN);
}
