#include "training.h"

void	*function_00(__attribute__((unused)) void *i)
{
	t_data		*data;
	pthread_t	thread = pthread_self();

	data = get_data(GET);
	printf(RED" 🎄 inside [%lu] START - %lu"RESET"\n", thread, *data->nbr);
	usleep (100);
	*data->nbr = 1;
	printf(RED" 🎄 inside [%lu] END   - %lu"RESET"\n", thread, *data->nbr);
	pthread_exit(NULL);
	return (NULL);

}

void	*function_01(__attribute__((unused)) void *i)
{
	t_data		*data;
	pthread_t	thread = pthread_self();

	data = get_data(GET);
	printf(BLUE" ❄️ inside [%lu] START - %lu"RESET"\n", thread, *data->nbr);
	usleep (100);
	*data->nbr = 100;
	printf(BLUE" ❄️ inside [%lu] END   - %lu"RESET"\n", thread, *data->nbr);
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
