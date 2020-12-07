#include "philo_one.h"

static void	debug_struct(void)			// TODO: REMOVE
{
	t_data	*data;

	data = get_data(GET);
	printf("data:\n");
	printf("->nb_philo         = %d\n", data->nb_philo);
	printf("->nb_dead_philo    = %d\n", data->nb_dead_philo);
	printf("->nb_forks         = %d\n", data->nb_forks);
	printf("->nb_philo         = %d\n", data->nb_philo);
	printf("->usec[T_TO_DIE]   = %d \n", data->param[T_TO_DIE]);
	printf("->usec[T_TO_EAT]   = %d \n", data->param[T_TO_EAT]);
	printf("->usec[T_TO_SLEEP] = %d \n", data->param[T_TO_SLEEP]);
	printf("->nb_eat_turns     = %d \n", data->nb_eat_turns);
}

int main(const int ac, const char **av)
{
	t_data	data;
	int		ret;

	get_data(&data);
	memset(&data, 0, sizeof(t_data));
debug_struct();			// TODO: remove
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
	process_philo(&data);
	return (0);
}
