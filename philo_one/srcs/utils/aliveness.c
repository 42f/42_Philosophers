#include "philo_one.h"

static bool	is_alive(t_data *data, const int philo_id)
{
	unsigned long	t_delta;
	// unsigned long	t_curr;
	// unsigned long	t_last_m;

	t_delta = get_current_time() - data->last_meal[philo_id];
	// t_curr = get_current_time();
	// t_last_m = data->last_meal[philo_id];
	// t_delta = t_curr - t_last_m;
	// printf("[%ld] - [%ld] = Delta = %ld\n",t_curr, t_last_m,t_delta);			// TODO: remove FOBIDDEN
	return(t_delta < (unsigned long)data->param[T_TO_DIE]);
}

t_state		check_aliveness(t_data *data, int philo_id,
													const t_state current_state)
{
	t_state		ret_state;

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

