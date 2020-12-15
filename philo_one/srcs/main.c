/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:07 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/15 16:09:37 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	is_digit_only(const char *av)
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

static void	*malloc_and_set(size_t size, int set_value)
{
	void	*new_mem;
	size_t	nb_philo;

	nb_philo = get_data(GET)->param[NB_PHILO];
	new_mem = malloc(size * (nb_philo + 1));
	if (new_mem == NULL)
		exit_routine(CODE_ERR_MALLOC);
	return (memset(new_mem, set_value, size * nb_philo + 1));
}

static void	init_philo_info_storage(t_data *data)
{
	data->last_meal = (unsigned long *)malloc_and_set(sizeof(unsigned long), 0);
	data->nb_meals_eaten = (int *)malloc_and_set(sizeof(int), 0);
	data->done_report_flag = (bool *)malloc_and_set(sizeof(bool), false);
	data->philo_fork = (bool *)malloc_and_set(sizeof(bool), FORK_AVAILABLE);
	data->philo_state_time_stamp = (unsigned long *)malloc_and_set(sizeof(unsigned long), 0);
	data->mutex_fork = (pthread_mutex_t *)malloc_and_set(sizeof(pthread_mutex_t), 0);
}

static void	free_data_struct_content(t_data *data)
{
		safe_free(data->last_meal);
		safe_free(data->nb_meals_eaten);
		safe_free(data->done_report_flag);
		safe_free(data->philo_fork);
		safe_free(data->philo_state);
		safe_free(data->philo_state_time_stamp);
		safe_free(data->mutex_fork);
		get_data(REMOVE);
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
