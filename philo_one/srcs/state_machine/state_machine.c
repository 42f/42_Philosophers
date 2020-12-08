#include "philo_one.h"

static t_state		wake_up_action_handler(t_data *data, const int philo_id)
{
	put_status(data, philo_id, MESSAGE_IS_THINKING);
	return (thinking_state);
}

static t_state		take_fork_action_handler(t_data *data, const int philo_id)
{
	//mutex fork
	put_status(data, philo_id, MESSAGE_HAS_TAKEN_FORK);
	put_status(data, philo_id, MESSAGE_IS_EATING);
	data->last_meal[philo_id] = get_current_time();
	data->nb_meals_eaten[philo_id]++;
	usleep(data->param[T_TO_EAT]);
	return (eating_state);
}

static t_state		drop_fork_action_handler(t_data *data, const int philo_id)
{
	put_status(data, philo_id, MESSAGE_IS_SLEEPING);
	usleep(data->param[T_TO_SLEEP]);
	return (sleeping_state);
}

static bool			check_loop_conditions(const t_state state,
										const t_data *data, const int philo_id)
{
	if (data->param[NB_MEALS] == UNSET)
		return (state != dead_state && data->death_report_flag == false);
	else
		return (state != dead_state
			&& data->death_report_flag == false
			&& data->nb_meals_eaten[philo_id] < data->param[NB_MEALS]);
}

void			*philo_state_machine(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	state = startup_state;
	while(check_loop_conditions(state, data, philo_id) == true)
	{
		state = check_aliveness(data, philo_id, state);
		if (state == thinking_state || state == startup_state )
			state = take_fork_action_handler(data, philo_id);
		else if (state ==  eating_state)
			state = drop_fork_action_handler(data, philo_id);
		else if (state == sleeping_state)
			state = wake_up_action_handler(data, philo_id);
	}
	if (state == dead_state)
		put_status(data, philo_id, MESSAGE_IS_DEAD);
	pthread_exit(NULL);
}
