#include "philo_one.h"

unsigned long get_current_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);	// check failure here
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

void			put_status(int philo_id, const char *message)
{
	ft_putnbr(get_current_time());
	ft_putnbr(philo_id);
	ft_put_str_fd(STDOUT_FILENO, message);
}

t_state		check_aliveness(t_data *data, int philo_id,
													const t_state current_state)
{
	static unsigned long t_delta;

	t_delta = get_current_time() - data->last_meal[philo_id];
	return ((t_delta < (unsigned long)data->param[T_TO_DIE]) ? current_state : dead_state);
	// if (t_delta < (unsigned long)data->param[T_TO_DIE])
	// 	return (current_state);
	// else
	// {
	// 	put_status(philo_id, MESSAGE_IS_DEAD);
	// 	ft_put_str_fd(STDERR_FILENO, "t_delta @ =");
	// 	ft_putnbr(t_delta);
	// 	ft_put_str_fd(STDERR_FILENO, "Last meal @ =");
	// 	ft_putnbr(data->last_meal[philo_id]);
	// 	ft_put_str_fd(STDERR_FILENO, "Meals eaten =");
	// 	ft_putnbr(data->nb_meals_eaten[philo_id]);
	// 	return (dead_state);
	// }
}
