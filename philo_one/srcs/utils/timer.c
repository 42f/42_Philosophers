#include "philo_one.h"

unsigned long get_current_time(void)
{
	static unsigned long long	origin_time;
	unsigned long long			current_time;
	struct timeval			time;

	if (gettimeofday(&time, NULL) != 0)
		exit (1);									// check failure here
	// current_time = (time.tv_sec * 100000) + time.tv_usec) / 1000;
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (origin_time == 0)
		origin_time = current_time;
	// printf("pf ------------------ %lld\n", current_time - origin_time);
	// ft_put_str_fd(STDOUT_FILENO, "INSIDE timer ============ ");
	// ft_putnbr(current_time - origin_time);
	// ft_put_str_fd(STDOUT_FILENO, "\n");
	return (current_time - origin_time);
}
