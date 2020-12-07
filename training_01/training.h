#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define		GET		NULL

#define		BLACK 	"\033[0;30m"
#define		RED 	"\033[0;31m"
#define		GREEN 	"\033[0;32m"
#define		YELLOW 	"\033[0;33m"
#define		BLUE 	"\033[0;34m"
#define		PURPLE 	"\033[0;35m"
#define		CYAN 	"\033[0;36m"
#define		WHITE 	"\033[0;37m"
#define		RESET 	"\033[0m"

typedef struct	s_data
{
	pthread_mutex_t	mutex;
	long int		*nbr;
}				t_data;

void			*function_00(void *i);
void			*function_01(void *i);
t_data			*get_data(t_data *mem);
