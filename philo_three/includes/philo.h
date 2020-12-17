/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:12:45 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/17 15:22:51 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

# define BUFF_SIZE			32

# define GET				NULL
# define UNSET				-1

# define FORK_AVAILABLE		true
# define FORK_USED			false
# define HAND_HAS_FORK		true
# define HAND_EMPTY			false

# define SUCCESS			1
# define FAILURE			-1

# define CHILD_FAILURE		1
# define CHILD_IS_DEAD		42
# define NO_OPTIONS			0
# define ANY_CHILD			-1
# define EVERY_CHILDREN		0
# define CHILD_PROCESS_PID	0

# define SUCCESS_RETURN		0
# define FAILURE_RETURN		1

# define SEM_NAME_RACE_STARTER	"/philo_race_starter"
# define SEM_NAME_STDOUT		"/philo_stdout"
# define SEM_NAME_FORKS_HEAP	"/philo_forks_heap"
# define SEM_NAME_DEATH_REPORT	"/philo_death_report"

# define USAGE0	"Philo: Usage: > 1 value only\n"
# define USAGE1	"number_of_philosopher time_to_die "
# define USAGE2	"time_to_eat time_to_sleep\n"
# define USAGE3	"[number_of_time_each_philosophers_must_eat]\n"

# define ERR_MALLOC		"\nPhilo: error: malloc() failed\n"
# define ERR_FORK		"\nPhilo: error: could not fork a sub process  \n"
# define ERR_SEM		"\nPhilo: error: could not initialize semaphore\n"
# define ERR_PTHREAD	"\nPhilo: error: pthread function failed\n"

# define NB_ERR_CODE	4

typedef enum	e_code_err
{
	CODE_ERR_MALLOC,
	CODE_ERR_FORK,
	CODE_ERR_SEM,
	CODE_ERR_PTHREAD
}				t_code_err;

# define MESSAGE_HAS_FORK_L			"has LEFT    fork\n"
# define MESSAGE_HAS_FORK_R			"has   RIGHT fork\n"
# define MESSAGE_HAS_FORK			"has taken a fork\n"
# define LEN_HAS_FORK				17
# define MESSAGE_EATING			"is eating\n"
# define LEN_IS_EATING				10
# define MESSAGE_SLEEPING		"is sleeping\n"
# define LEN_IS_SLEEPING			12
# define MESSAGE_THINKING		"is thinking\n"
# define LEN_IS_THINKING			12
# define MESSAGE_DEAD			"died\n"
# define LEN_IS_DEAD				5

# define NB_OF_FORKS_NEEDED_TO_EAT		2
# define NB_OF_PARAM					5

enum	e_times_arguments
{
	NB_PHILO,
	T_TO_DIE,
	T_TO_EAT,
	T_TO_SLEEP,
	NB_MEALS
};

typedef enum	e_state
{
	no_state,
	startup_state,
	has_fork_state,
	eating_state,
	finished_meal_state,
	reached_meals_nb_state,
	sleeping_state,
	thinking_state,
	dead_state,
}				t_state;

typedef struct	s_global_data
{
	sem_t			*sem_race_starter;
	sem_t			*sem_stdout;
	sem_t			*sem_forks_heap;
	sem_t			*sem_death_report;
	int				param[NB_OF_PARAM];
	char			padd_00[4];
	pid_t			*philo_pids;
}				t_gdata;

typedef struct	s_data
{
	int				nb_meals_eaten;
	bool			death_report;
	bool			done_report_flag;
	char			padd_00[6];
	unsigned long	death_report_timestamp;
	unsigned long	current_clock;
	unsigned long	philo_state_time_stamp;
	unsigned long	last_meal;
	sem_t			*sem_race_starter;
	sem_t			*sem_stdout;
	sem_t			*sem_forks_heap;
	sem_t			*sem_death_report;
	int				param[NB_OF_PARAM];
	char			padd_01[4];
}				t_data;

/*
**	MONITOR
*/

void			*philo_monitor(void *i_arg);

/*
**	STATE_MACHINE
*/

void			child_process(t_gdata *global_data, int philo_id);
void			*philo_state_machine(void *i_arg);
void			process_fork(t_gdata *data);
t_state			check_aliveness(t_data *data, int philo_id,
										const t_state current_state, int time);
void			put_regular_status(t_data *data, const int philo_id,
								const int message_len, const char *message);
void			put_death_status(t_data *data, const int philo_id);

t_state			think_action_handler(t_data *data, const int philo_id);
t_state			take_forks_and_eat_handler(t_data *data, const int philo_id);
t_state			sleep_and_think_handler(t_data *data, const int philo_id);

int				get_right_philo_id(t_data *data, int philo_id);
void			aquire_forks(t_data *data, int philo_id);
void			report_nb_meals_reached_and_exit_thread(t_data *data,
									int philo_id) __attribute__((noreturn));

/*
**	TIMER
*/

void			*clock_routine(void *data_arg);

/*
**	UTILS
*/

t_data			*get_data(t_data *mem);
void			update_current_time(t_data *data);

void			init_sem(t_gdata *data);
void			destroy_sem(t_gdata *data);
void			safe_sem_close(sem_t *sem_to_close, const char* name);

void			failed_init_arrays(pthread_t *th_philo,
					pthread_t *th_monitor, int *philo_id);
void			init_threads_arr(pthread_t **th_philo,
					pthread_t **th_monitor, int **philo_id);

int				ft_put_str_fd(int fd, const char *s);
unsigned long	get_death_time(t_data *data);
int				ft_put_message_fd(int fd, const size_t len, const char *str);
int				ft_putnbr(int fd, unsigned long n);

void			safe_free(void *mem);
void			exit_routine_mainprocess(t_code_err err, t_gdata *gdata);
void			exit_routine_childprocess(t_code_err err);

/*
**	ARGUMENTS
*/

int				is_digit_only(const char *av);
int				process_arguments(t_gdata *data, const char **av);

#endif
