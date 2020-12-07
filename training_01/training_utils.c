#include "training.h"

int		get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);	// check failure here
	return (time.tv_usec);
}

void	*function_00(__attribute__((unused)) void *i)
{
	t_data		*data;
	pthread_t	thread = pthread_self();
	int			t0;
	int			t1;

	data = get_data(GET);
	// pthread_mutex_lock(&data->mutex);
	t0 = get_time();
	fprintf(stdout, RED"[%d] 🎄 inside [%lu] START - %lu"RESET"\n", t0, thread, *data->nbr);
	usleep(100);
	*data->nbr = 1;
	t1 = get_time();
	fprintf(stdout, RED"[%d] 🎄 inside [%lu] END   - %lu"RESET"\n", t1, thread, *data->nbr);
	// pthread_mutex_unlock(&data->mutex);
	fprintf(stdout, RED"[%d][%d][%d]"RESET"\n", t0, t1, t1 - t0);
	pthread_exit(NULL);
	return (NULL);

}

void	*function_01(__attribute__((unused)) void *i)
{
	t_data		*data;
	pthread_t	thread = pthread_self();

	data = get_data(GET);
	// pthread_mutex_lock(&data->mutex);
	fprintf(stdout, BLUE"[%d] ❄️ inside [%lu] START - %lu"RESET"\n", get_time(), thread, *data->nbr);
	usleep(100);
	*data->nbr = 100;
	fprintf(stdout, BLUE"[%d] ❄️ inside [%lu] END   - %lu"RESET"\n", get_time(), thread, *data->nbr);
	// pthread_mutex_unlock(&data->mutex);
	pthread_exit(NULL);
	return (NULL);

}

t_data	*get_data(t_data *mem)
{
	static t_data	*mem_backup = NULL;

	if (mem != GET)
		mem_backup = mem;
	return (mem_backup);
}
