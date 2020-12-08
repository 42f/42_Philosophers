#include "philo_one.h"

// static void	debug_struct(void)			// TODO: REMOVE
// {
// 	t_data	*data;

// 	data = get_data(GET);
// 	printf("data:\n");
// 	printf("->nb_dead_philo    = %d\n",  data->death_report_flag);
// 	printf("->nb_philo         = %d \n", data->param[NB_PHILO]);
// 	printf("->usec[T_TO_DIE]   = %d \n", data->param[T_TO_DIE]);
// 	printf("->usec[T_TO_EAT]   = %d \n", data->param[T_TO_EAT]);
// 	printf("->usec[T_TO_SLEEP] = %d \n", data->param[T_TO_SLEEP]);
// 	printf("->usec[NB_MEALS] = %d \n", data->param[NB_MEALS]);
// }

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

static void				put_usage(void)
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

static bool	init_meals_info_storage(t_data *data)
{
	data->last_meal = malloc(data->param[NB_PHILO] * sizeof(unsigned long));
	data->nb_meals_eaten = malloc(data->param[NB_PHILO] * sizeof(unsigned int));
	if (data->last_meal == NULL || data->nb_meals_eaten == NULL)
	{
		ft_put_str_fd(STDERR_FILENO, ERR_MALLOC);
		return (false);
	}
	memset(data->last_meal, 0, data->param[NB_PHILO] * sizeof(unsigned long));
	memset(data->nb_meals_eaten, 0, data->param[NB_PHILO] * sizeof(unsigned int));
	return (true);
}

int			main(const int ac, const char **av)
{
	t_data	data;
	int		ret;

	get_data(&data);
	memset(&data, 0, sizeof(t_data));
	ret = SUCCESS;
	ret = check_arguments(ac, av);
	if (ret != FAILURE)
		ret = process_arguments(&data, av);
	if (ret == FAILURE)
	{
		put_usage();
		return (1);
	}
// debug_struct();			// TODO: remove
	if (init_meals_info_storage(&data) == true)
	{
		process_philo(&data);
		free(data.last_meal);
		free(data.nb_meals_eaten);
	}
	return (0);
}
