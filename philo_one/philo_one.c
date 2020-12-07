#include "philo_one.h"

static void	debug_struct(void)
{
	t_data	*data;

	data = get_data(GET);
	printf("data:\n->nb_philo = %d\n", data->nb_philo);
	printf("->usec[T_TO_DIE] = %d \n", data->usec[T_TO_DIE]);
	printf("->usec[T_TO_EAT] = %d \n", data->usec[T_TO_EAT]);
	printf("->usec[T_TO_SLEEP] = %d \n", data->usec[T_TO_SLEEP]);
	printf("->nb_eat_turns = %d \n", data->nb_eat_turns);
}

int main(const int ac, const char **av)
{
	t_data	data;
	int		ret;

	get_data(&data);
	ret = SUCCESS;
	ret = check_arguments(ac, av);
	if (ret != FAILURE)
		ret = process_arguments(&data, av);
	if (ret == FAILURE)
	{
		put_usage();
		return (1);
	}

	debug_struct();

	return (0);
}
