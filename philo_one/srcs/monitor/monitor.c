#include "philo_one.h"

static bool		loop_condition(t_data *data, t_state state)
{
	usleep(2);
	return (state != dead_state && data->death_report_flag == false);
}

void			*philo_monitor(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	state = startup_state;
	while(loop_condition(data, state) == true)
		state = check_aliveness(data, philo_id, state);
	if (state == dead_state)
		put_status(data, philo_id, MESSAGE_IS_DEAD);
	pthread_exit(NULL);
}
