#include "philo_one.h"

static void			set_time(unsigned long *time_mem)
{
	*time_mem = get_current_time();
}

static t_state		wake_up_action_handler(t_data *data, const int philo_id)
{
	put_status(data, philo_id, MESSAGE_IS_THINKING);
	return (thinking_state);
}

static t_state		take_fork_action_handler(t_data *data, const int philo_id)
{
	put_status(data, philo_id, MESSAGE_HAS_TAKEN_FORK);
	set_time(&data->last_meal[philo_id]);
	put_status(data, philo_id, MESSAGE_IS_EATING);
	usleep(data->param[T_TO_EAT]);
	data->nb_meals_eaten[philo_id]++;
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

static void			*philo(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	state = startup_state;
	set_time(&data->last_meal[philo_id]);
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
	// dprintf(STDERR_FILENO, "ENDED LOOP FOR PHILO %d, state = %d\n", philo_id, state);
	if (state == dead_state)
		put_status(data, philo_id, MESSAGE_IS_DEAD);
	pthread_exit(NULL);
}

static void			destroy_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_stdout);
	pthread_mutex_destroy(&data->mutex_death_report);
}

static void			init_mutex(t_data *data)
{
	pthread_mutex_init(&data->mutex_stdout, NULL);
	pthread_mutex_init(&data->mutex_death_report, NULL);
}

void				process_philo(t_data *data)
{
	pthread_t		*thread;
	int				i;
	int				*philo_id;

	init_mutex(data);
	philo_id = (int *)malloc(data->param[NB_PHILO] * sizeof(int));
	thread = (pthread_t *)malloc(data->param[NB_PHILO] * sizeof(pthread_t));
	if (philo_id == NULL || thread == NULL)
		exit (1);									//TODO: exit_routine
	i = 0;
	while (i < data->param[NB_PHILO])
	{
		philo_id[i] = i;
		pthread_create(&thread[i], NULL, philo, &philo_id[i]);
		i++;
	}
	i = 0;
	while (i < data->param[NB_PHILO])
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	destroy_mutex(data);
	free(thread);
	free(philo_id);
}
