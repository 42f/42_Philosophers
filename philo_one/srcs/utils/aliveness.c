#include "philo_one.h"

static bool	is_alive(t_data *data, const int philo_id)
{
	static int	t_delta;

	t_delta = get_current_time() - data->last_meal[philo_id];
	return(t_delta < convert_from_usec_to_msec(data->param[T_TO_DIE])
			|| data->param[NB_MEALS] != UNSET);
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
