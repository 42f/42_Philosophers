/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:07 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 13:35:42 by bvalette         ###   ########.fr       */
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

static void	init_philo_info_storage(t_data *data, int nb_philo)
{
	nb_philo += 1;
	data->last_meal = malloc(nb_philo * sizeof(unsigned long));
	data->nb_meals_eaten = malloc(nb_philo * sizeof(int));
	data->done_report_flag = malloc(nb_philo * sizeof(bool));
	data->philo_fork = malloc(nb_philo * sizeof(bool));
	data->philo_state = malloc(nb_philo * sizeof(t_state));
	data->philo_state_time_stamp = malloc(nb_philo * sizeof(unsigned long));
	data->mutex_fork = malloc(nb_philo * sizeof(pthread_mutex_t));
	data->mutex_last_meal = malloc(nb_philo * sizeof(pthread_mutex_t));
	if (data->last_meal == NULL|| data->nb_meals_eaten == NULL
		|| data->done_report_flag == NULL || data->philo_fork == NULL
		|| data->philo_state == NULL|| data->mutex_fork == NULL)
		exit_routine(CODE_ERR_MALLOC);
		//CHECK THIS LIST
	memset(data->last_meal, 0, nb_philo * sizeof(unsigned long));
	memset(data->nb_meals_eaten, 0, nb_philo * sizeof(int));
	memset(data->done_report_flag, false, nb_philo * sizeof(bool));
	memset(data->philo_fork, FORK_AVAILABLE, nb_philo * sizeof(bool));
	memset(data->philo_state, startup_state, nb_philo * sizeof(t_state));
	memset(data->philo_state_time_stamp, 0, nb_philo * sizeof(unsigned long));
	memset(data->mutex_fork, 0, nb_philo * sizeof(pthread_mutex_t));
	memset(data->mutex_last_meal, 0, nb_philo * sizeof(pthread_mutex_t));
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
		init_philo_info_storage(&data, data.param[NB_PHILO]);
		process_philo(&data);
		safe_free(data.last_meal);
		safe_free(data.nb_meals_eaten);
		safe_free(data.done_report_flag);
		safe_free(data.philo_fork);
		safe_free(data.philo_state);
		safe_free(data.philo_state_time_stamp);
		safe_free(data.mutex_fork);
		get_data(REMOVE);
	}
	else
	{
		put_usage();
		return (FAILURE_RETURN);
	}
	return (SUCCESS_RETURN);
}
