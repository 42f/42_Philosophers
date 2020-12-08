#include "philo_one.h"

static void			destroy_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_stdout);
	pthread_mutex_destroy(&data->mutex_death_report);
}

static void			init_mutex(t_data *data)
{
	pthread_mutex_init(&data->mutex_stdout, NULL);						// TODO: check fails
	pthread_mutex_init(&data->mutex_death_report, NULL);
}

static void			init_arrays(pthread_t **th_philo,
					pthread_t **th_monitor, int **philo_id, size_t nb_philo)
{
	*philo_id = (int *)malloc(nb_philo * sizeof(int));
	*th_philo = (pthread_t *)malloc(nb_philo * sizeof(pthread_t));
	*th_monitor = (pthread_t *)malloc(nb_philo * sizeof(pthread_t));
	if (*philo_id == NULL || *th_philo == NULL || *th_monitor == NULL)
		exit (1);														//TODO: exit_routine
}

void				process_philo(t_data *data)
{
	pthread_t		*th_philo;
	pthread_t		*th_monitor;
	int				i;
	int				*philo_id;

	init_mutex(data);
	init_arrays(&th_philo, &th_monitor, &philo_id, data->param[NB_PHILO] + 1);
	i = 1;
	while (i < data->param[NB_PHILO])
	{
		philo_id[i] = i;
		pthread_create(&th_philo[i], NULL, philo_state_machine, &philo_id[i]);
		// pthread_create(&th_monitor[i], NULL, philo_monitor, &philo_id[i]);
		i++;
	}
	i = 0;
	while (i < data->param[NB_PHILO])
	{
		pthread_join(th_philo[i], NULL);
		// pthread_join(th_monitor[i], NULL);
		i++;
	}
	destroy_mutex(data);
	free(th_philo);
	free(th_monitor);
	free(philo_id);
}
