#include "philo_one.h"


static unsigned long get_current_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);	// check failure here
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

static void			put_status(int philo_id, const char *message)
{
	ft_putnbr(get_current_time());
	ft_putnbr((unsigned int)philo_id);
	ft_put_str_fd(STDOUT_FILENO, message);
}

static t_state		check_aliveness(t_data *data, int philo_id,
													const t_state current_state)
{
	static unsigned long t_delta;

	t_delta = get_current_time() - data->last_meal[philo_id];
	if (t_delta > (unsigned long)data->param[T_TO_DIE])
	{
		put_status(philo_id, MESSAGE_IS_DEAD);
		ft_put_str_fd(STDOUT_FILENO, "t_delta @ =");
		ft_putnbr(t_delta);
		ft_put_str_fd(STDOUT_FILENO, "Last meal @ =");
		ft_putnbr(data->last_meal[philo_id]);
		ft_put_str_fd(STDOUT_FILENO, "Meals eaten =");
		ft_putnbr(data->nb_meals_eaten[philo_id]);
		return (dead_state);
	}
	else
		return (current_state);
}

static void			set_time(unsigned long *time_mem)
{
	*time_mem = get_current_time();
}

static t_state		wake_up_action_handler(const int philo_id)
{
	put_status(philo_id, MESSAGE_IS_THINKING);
	return (thinking_state);
}

static t_state		take_fork_action_handler(t_data *data, const int philo_id)
{
	put_status(philo_id, MESSAGE_HAS_TAKEN_FORK);
	set_time(&data->last_meal[philo_id]);
	put_status(philo_id, MESSAGE_IS_EATING);
	usleep(data->param[T_TO_EAT]);
	data->nb_meals_eaten[philo_id]++;
	return (eating_state);
}

static t_state		drop_fork_action_handler(t_data *data, const int philo_id)
{
	put_status(philo_id, MESSAGE_IS_SLEEPING);
	usleep(data->param[T_TO_SLEEP]);
	return (sleeping_state);
}

static void			*philo(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *(int *)i_arg;
	state = startup_state;
	set_time(&data->last_meal[philo_id]);
	while(state != dead_state)
	{
		state = check_aliveness(data, philo_id, state);
		if (state == thinking_state || state == startup_state )
			state = take_fork_action_handler(data, philo_id);
		else if (state ==  eating_state)
			state = drop_fork_action_handler(data, philo_id);
		else if (state == sleeping_state)
			state = wake_up_action_handler(philo_id);
	}
	return (NULL);
	// pthread_exit(NULL);
}

void				process_philo(t_data *data)
{
	pthread_t		thread;
	unsigned int	i;

	i = 0;
	philo(&i);
	return ;

	while (i < data->param[NB_PHILO])
	{
		pthread_create(&thread, NULL, philo, (void *)((long int)i));
		i++;
	}
	pthread_exit(NULL);
}
