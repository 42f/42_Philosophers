#include "philo_one.h"

unsigned long t_delta;

static unsigned long get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);	// check failure here
	return ((unsigned long)((time.tv_sec * 1000000) + time.tv_usec));
}

static void			put_status(int philo_id, const char *message)
{
	ft_putnbr(get_current_time());
	write(STDERR_FILENO, " ", 1);
	ft_putnbr((unsigned int)philo_id);
	write(STDERR_FILENO, " ", 1);
	ft_put_str_fd(STDERR_FILENO, message);
}
static void	ft_writenbr(unsigned int c)
{
	c += '0';
	write(STDERR_FILENO, &c, 1);
}

void		ft_putnbr_err(unsigned int n)
{

	if (n >= 10)
		ft_putnbr(n / 10);
	ft_writenbr(n % 10);
	write(STDERR_FILENO, "\n", 1);
}

static t_state		check_aliveness(t_data *data, int philo_id,
													const t_state current_state)
{
	t_delta = get_current_time() - data->last_meal[philo_id];
	if (t_delta > (unsigned long)data->param[T_TO_DIE])
	{
		put_status(philo_id, MESSAGE_IS_DEAD);
		ft_putnbr_err(t_delta);
		ft_putnbr_err(data->last_meal[philo_id]);
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

	t_delta = 0;
	data = get_data(GET);
	philo_id = *(int *)i_arg;
	state = startup_state;
	set_time(&data->last_meal[philo_id]);
	// printf("time = [%d], last meal = [%d]\n", get_current_time(), data->last_meal[philo_id]);
	while(state != dead_state)
	{
		state = check_aliveness(data, philo_id, state);
		if (state == startup_state || state == thinking_state)
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
