/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:07 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 11:23:24 by bvalette         ###   ########.fr       */
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

int			main(const int ac, const char **av)
{
	t_gdata	global_data;
	int		ret;

	memset(&global_data, 0, sizeof(t_gdata));
	ret = check_arguments(ac, av);
	if (ret == SUCCESS)
		ret = process_arguments(&global_data, av);
	if (ret == SUCCESS)
		process_fork(&global_data);
	else
	{
		put_usage();
		return (FAILURE_RETURN);
	}
	return (SUCCESS_RETURN);
}
