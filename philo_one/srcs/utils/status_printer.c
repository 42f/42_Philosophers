#include "philo_one.h"

void			put_status(t_data *data, const int philo_id, const char *message)
{
	unsigned long	time;

	time = get_current_time();
	pthread_mutex_lock(&data->mutex_stdout);
	ft_putnbr(time);
	ft_putnbr(philo_id);
	ft_put_str_fd(STDOUT_FILENO, message);
	pthread_mutex_unlock(&data->mutex_stdout);
}
