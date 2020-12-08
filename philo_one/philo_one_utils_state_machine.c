#include "philo_one.h"

unsigned long get_current_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);	// check failure here
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

void			put_status(t_data *data, const int philo_id, const char *message)
{
	pthread_mutex_lock(&data->mutex_stdout);
	ft_putnbr(get_current_time());
	ft_putnbr(philo_id);
	ft_put_str_fd(STDOUT_FILENO, message);
	pthread_mutex_unlock(&data->mutex_stdout);
}

// static void	debug_death(const unsigned long t_delta, t_data *data,
// 															const int philo_id)
// {
// 		put_status(data, philo_id, MESSAGE_IS_DEAD);
// 		ft_put_str_fd(STDERR_FILENO, "t_delta @ =");
// 		ft_putnbr(t_delta);
// 		ft_put_str_fd(STDERR_FILENO, "Last meal @ =");
// 		ft_putnbr(data->last_meal[philo_id]);
// 		ft_put_str_fd(STDERR_FILENO, "Meals eaten =");
// 		ft_putnbr(data->nb_meals_eaten[philo_id]);
// }

static bool	is_alive(t_data *data, const int philo_id)
{
	static unsigned long t_delta;

	t_delta = get_current_time() - data->last_meal[philo_id];
	return(t_delta < (unsigned long)data->param[T_TO_DIE]
											|| data->param[NB_MEALS] != UNSET);

}

t_state		check_aliveness(t_data *data, int philo_id,
													const t_state current_state)
{
	t_state				ret_state;

	ret_state = current_state;
	if (is_alive(data, philo_id) == false)
	{
		pthread_mutex_lock(&data->mutex_death_report);
		if (data->death_report_flag == false)
		{
			data->death_report_flag = true;
			pthread_mutex_unlock(&data->mutex_death_report);
			ret_state = dead_state;
		}
		else
		{
			pthread_mutex_unlock(&data->mutex_death_report);
			ret_state = current_state;
		}
	}
	return (ret_state);
}
