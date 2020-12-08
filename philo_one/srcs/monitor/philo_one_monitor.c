#include "philo_one.h"

void			*philo_monitor(void *i_arg)
{
	(void)i_arg;
	pthread_exit(NULL);
}
