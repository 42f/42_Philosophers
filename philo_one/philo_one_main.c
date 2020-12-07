#include "philo_one.h"

static void	debug_struct(void)			// TODO: REMOVE
{
	t_data	*data;

	data = get_data(GET);
	printf("data:\n");
	printf("->nb_dead_philo    = %d\n", data->nb_dead_philo);
	printf("->nb_philo         = %d \n", data->param[NB_PHILO]);
	printf("->usec[T_TO_DIE]   = %d \n", data->param[T_TO_DIE]);
	printf("->usec[T_TO_EAT]   = %d \n", data->param[T_TO_EAT]);
	printf("->usec[T_TO_SLEEP] = %d \n", data->param[T_TO_SLEEP]);
	printf("->usec[NB_MEALS] = %d \n", data->param[NB_MEALS]);
}

static bool	init_last_eat_time_storage(t_data *data)
{
	data->last_meal = malloc(sizeof(int) * data->param[NB_PHILO]);
	data->nb_meals_eaten = malloc(sizeof(int) * data->param[NB_PHILO]);
	if (data->last_meal == NULL || data->nb_meals_eaten == NULL)
	{
		ft_put_str_fd(STDERR_FILENO, ERR_MALLOC);
		return (false);
	}
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
debug_struct();			// TODO: remove
	if (init_last_eat_time_storage(&data) == true)
		process_philo(&data);
	return (0);
}
