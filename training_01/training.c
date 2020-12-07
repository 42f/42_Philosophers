#include "training.h"

int main()
{
	pthread_t	thread[2];
	long int	i;
	t_data		data;

	get_data(&data);
	i = 0;
	data.nbr = &i;
	pthread_mutex_init(&data.mutex, NULL);
	printf("\n\nMAIN before i = %lu\n", i);

	pthread_create(&thread[1], NULL, function_01, NULL);
	pthread_create(&thread[0], NULL, function_00, NULL);

	i = 42;


	printf(YELLOW"cancel {%lu}"RESET"\n", thread[0]);
	pthread_cancel(thread[0]);
	usleep (100);
	printf("\n\nduring i = %lu\n", i);
	// printf("cancel {%lu}\n", thread[1]);
	// pthread_cancel(thread[1]);


	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_mutex_destroy(&data.mutex);


	printf("MAIN returned i = %lu\n", i);
	return (0);
}
