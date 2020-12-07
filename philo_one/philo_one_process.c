#include "philo_one.h"

// 		check_aliveness(void)
// {
// 	t_data			*data;
// 	unsigned int	current_time;

// 	data = get_data(GET);
// 	set_time(&current_time);
// 	if (current_time - data->last_time[T_TO_EAT] > data->param[T_TO_EAT])
// 		return (dead_)
// }

// static void		set_time(unsigned int* time_mem)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);	// check failure here
// 	time_mem = time.tv_usec;
// }

static t_state	wake_up_action_handler(t_data *data, int philo_id)
{
	(void)data;
	printf("Philo %d is thinking\n", philo_id);
	usleep(1 * 1000000);
	return (thinking_state);
}

static t_state	take_fork_action_handler(t_data *data, int philo_id)
{
	// try to get mutex
	(void)data;
	printf("Philo %d has taken fork\n", philo_id);
	return (eating_state);
}

static t_state	drop_fork_action_handler(t_data *data, int philo_id)
{
	(void)data;
	printf("Philo %d is sleeping\n", philo_id);
	usleep(1 * 1000000);
	return (sleeping_state);
}

static void	*philo(void *i_arg)
{
	// printf("thread %03lu\n", (long int)i);
	int			philo_id;
	t_data		*data;
	t_state		state;

	data = get_data(GET);
	philo_id = (int)((long int)i_arg);
	state = startup_state;
	while(state != dead_state)
	{
		if (state == startup_state)
			state = take_fork_action_handler(data, philo_id);
		else if (state ==  eating_state)
		{
			printf(RED"Philo %d is eating\n"RESET, philo_id);
			usleep(data->param[T_TO_EAT]);
			state = drop_fork_action_handler(data, philo_id);
		}
		else if (state == sleeping_state)
		{
			printf(GREEN"Philo %d is sleeping\n"RESET, philo_id);
			usleep(data->param[T_TO_SLEEP]);
			state = wake_up_action_handler(data, philo_id);
		}
		else if (state == thinking_state)
		{
			printf(YELLOW"Philo %d is thinking\n"RESET, philo_id);
			state = take_fork_action_handler(data, philo_id);
		}
	}
	printf("Philo %d is deaaaad 💀 \n", (int)((long int)i_arg));
	pthread_exit(NULL);
}

void process_philo(t_data *data)
{
	pthread_t	thread;
	int			i;

	i = 0;
	philo(&i);
	return ;


	while (i < data->nb_philo)
	{
		pthread_create(&thread, NULL, philo, (void *)((long int)i));
		i++;
	}
	pthread_exit(NULL);
}
