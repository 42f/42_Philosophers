/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:12:45 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 16:55:49 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

# define GET				NULL
# define REMOVE				(void *)0xffffffffffffffff
# define UNSET				-1

# define FORK_AVAILABLE		true
# define FORK_USED			false
# define HAND_HAS_FORK		true
# define HAND_EMPTY			false

# define SUCCESS			1
# define FAILURE			-1

# define SUCCESS_RETURN		0
# define FAILURE_RETURN		1

# define USAGE0	"Philo: Usage: positive value only\n"
# define USAGE1	"number_of_philosopher time_to_die "
# define USAGE2	"time_to_eat time_to_sleep\n"
# define USAGE3	"[number_of_time_each_philosophers_must_eat]\n"

# define ERR_MALLOC		"\nPhilo: error: malloc() failed\n"
# define ERR_MUTEX		"\nPhilo: error: could not initialize mutex\n"
# define ERR_PTHREAD	"\nPhilo: error: pthread function failed\n"

# define NB_ERR_CODE	3

typedef enum	e_code_err
{
	CODE_ERR_MALLOC,
	CODE_ERR_MUTEX,
	CODE_ERR_PTHREAD
}				t_code_err;

// # ifndef DEBUG_MODE

#  define MESSAGE_HAS_TAKEN_LEFT_FORK	"has taken a LEFT fork\n"
#  define MESSAGE_HAS_TAKEN_RIGHT_FORK	"has taken a RIGHT fork\n"
#  define MESSAGE_HAS_TAKEN_FORK	"has taken a fork\n"
#  define MESSAGE_IS_EATING			"is eating\n"
#  define MESSAGE_IS_SLEEPING		"is sleeping\n"
#  define MESSAGE_IS_THINKING		"is thinking\n"
#  define MESSAGE_IS_DEAD			"died\n"

// # else

// #  define MESSAGE_HAS_TAKEN_FORK	"\033[0;31mhas taken a fork\033[0m\n"
// #  define MESSAGE_IS_EATING			"\033[0;32mis eating\033[0m\n"
// #  define MESSAGE_IS_SLEEPING		"\033[0;34mis sleeping\033[0m\n"
// #  define MESSAGE_IS_THINKING		"\033[0;33mis thinking\033[0m\n"
// #  define MESSAGE_IS_DEAD			"\033[0;35mdied\033[0m\n"

// # endif

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

typedef struct	s_data
{
	bool			first_death_report;
	bool			first_done_report;
	char			padding_00[6];
	int				active_printer_count;
	unsigned long	current_clock;
	bool			*done_report_flag;
	bool			*philo_fork;
	t_state			*philo_state;
	unsigned long	*philo_state_time_stamp;
	int				*nb_meals_eaten;
	unsigned long	*last_meal;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mutex_last_meal;
	pthread_mutex_t	mutex_stderr;
	pthread_mutex_t	mutex_stdout;
	pthread_mutex_t	mutex_death_report;
	int				param[NB_OF_PARAM];
}				t_data;

typedef void (*t_printer)(t_data*, const int, unsigned long, const char*);

typedef struct s_printer_data
{
	t_printer		printer_routine;
	int				philo_id;
	unsigned long	time;
	const char		*message;
}				t_printer_data;


/*
**	MONITOR
*/

void			*philo_monitor(void *i_arg) __attribute__((noreturn));
bool			is_alive(t_data *data, const int philo_id);

/*
**	STATE_MACHINE
*/

void			*philo_state_machine(void *i_arg) __attribute__((noreturn));
void			process_philo(t_data *data);
t_state			check_aliveness(t_data *data, int philo_id,
												const t_state current_state);
void			put_death_status(t_data *data, const int philo_id,
										unsigned long time, const char *message);
void			put_regular_status(t_data *data, const int philo_id,
										unsigned long time, const char *message);

void			acquire_forks(t_data *data, int philo_id);
void			drop_forks(t_data *data, int philo_id);

t_state			think_action_handler(t_data *data, const int philo_id);
t_state			take_forks_and_eat_action_handler(t_data *data, const int philo_id);
t_state			sleep_action_handler(t_data *data, const int philo_id);

int				get_right_philo_id(t_data *data, int philo_id);

void			done_eating_action_handler(t_data *data, const int philo_id);

void			create_printer(t_printer printer, int philo_id,
									unsigned long time, const char *message);
/*
**	TIMER
*/

unsigned long	get_current_time(void);
void			*clock_routine(void *data_arg);

/*
**	UTILS
*/
void			init_mutex(t_data *data);
void			failed_init_arrays(pthread_t *th_philo,
					pthread_t *th_monitor, int *philo_id);
void			init_threads_arr(pthread_t **th_philo,
					pthread_t **th_monitor, int **philo_id, size_t nb_philo);
t_data			*get_data(t_data *mem);
void			ft_put_str_fd(int fd, const char *s);
int				ft_putnbr(int fd, unsigned long n);

void			destroy_mutex(t_data *data);
void			safe_free(void *mem);
void			exit_routine(t_code_err err) __attribute__((noreturn));

/*
**	ARGUMENTS
*/

int				process_arguments(t_data *data, const char **av);

#endif
