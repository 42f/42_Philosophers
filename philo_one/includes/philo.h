/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:12:45 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/21 07:48:18 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

# define BUFF_SIZE			32

# define GET				NULL
# define UNSET				-1

# define FORK_AVAILABLE		true
# define FORK_USED			false
# define HAND_HAS_FORK		true
# define HAND_EMPTY			false

# define SUCCESS			1
# define FAILURE			-1

# define SUCCESS_RETURN		0
# define FAILURE_RETURN		1

# define USAGE0	"Philo: Usage: > 1 value only, no more than 200 philosophers\n"
# define USAGE1	"number_of_philosopher time_to_die time_to_eat time_to_sleep\n"
# define USAGE2	"[number_of_time_each_philosophers_must_eat]\n"
# define USAGE3	"Max philo number: 200, minimum times 60\n"

# define ERR_MALLOC		"\nPhilo: error: malloc() failed\n"
# define ERR_MUTEX		"\nPhilo: error: could not initialize mutex\n"
# define ERR_PTHREAD	"\nPhilo: error: pthread function failed\n"

# define NB_ERR_CODE			3

typedef enum	e_code_err
{
	CODE_ERR_MALLOC,
	CODE_ERR_MUTEX,
	CODE_ERR_PTHREAD,
	CODE_ERR_NORMAL_EXIT = -1
}				t_code_err;

# define MESSAGE_HAS_FORK_L			"has LEFT    fork\n"
# define MESSAGE_HAS_FORK_R			"has   RIGHT fork\n"
# define MESSAGE_HAS_FORK			"has taken a fork\n"
# define LEN_HAS_FORK				17
# define MESSAGE_EATING				"is eating\n"
# define LEN_IS_EATING				10
# define MESSAGE_SLEEPING			"is sleeping\n"
# define LEN_IS_SLEEPING			12
# define MESSAGE_THINKING			"is thinking\n"
# define LEN_IS_THINKING			12
# define MESSAGE_DEAD				"died\n"
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

typedef struct	s_data
{
	bool			first_death_report;
	char			padd_00[7];
	int				nb_philo_done;
	char			padd_01[4];
	int				param[NB_OF_PARAM];
	char			padd_02[4];
	unsigned long	first_death_report_timestamp;
	unsigned long	current_clock;
	bool			*done_report_flag;
	bool			*philo_fork;
	t_state			*philo_state;
	unsigned long	*philo_state_time_stamp;
	int				*nb_meals_eaten;
	unsigned long	*last_meal;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_race_starter;
	pthread_mutex_t	mutex_nb_philo_done_counter;
	pthread_mutex_t	mutex_stdout;
	pthread_mutex_t	mutex_death_report;
}				t_data;

/*
**	MONITOR
*/

void			*philo_monitor(void *i_arg);

/*
**	STATE_MACHINE
*/

void			*philo_state_machine(void *i_arg);
int				process_philo(t_data *data);
t_state			check_aliveness(t_data *data, int philo_id,
										const t_state current_state, int time);
void			put_regular_status(t_data *data, const int philo_id,
								const int message_len, const char *message);
void			put_death_status(t_data *data, const int philo_id);

void			acquire_forks(t_data *data, int philo_id);
void			drop_forks(t_data *data, int philo_id);

t_state			think_action_handler(t_data *data, const int philo_id);
t_state			take_forks_and_eat_handler(t_data *data, const int philo_id);
t_state			sleep_and_think_handler(t_data *data, const int philo_id);

int				get_right_philo_id(t_data *data, int philo_id);
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

int				init_mutex(t_data *data);
void			destroy_mutex(t_data *data);

void			failed_init_arrays(pthread_t *th_philo,
					pthread_t *th_monitor, int *philo_id);
int				init_threads_arr(pthread_t **th_philo,
					pthread_t **th_monitor, int **philo_id);

int				ft_put_str_fd(int fd, const char *s);
unsigned long	get_death_time(t_data *data, int philo_id);
int				ft_put_message_fd(int fd, const size_t len, const char *str);
int				ft_putnbr(int fd, unsigned long n);

void			*malloc_and_set(size_t size, int set_value);
void			free_data_struct_content(t_data *data);
void			safe_free(void *mem);
int				cleanup_routine(t_code_err err);

/*
**	ARGUMENTS
*/

int				is_digit_only(const char *av);
int				process_arguments(t_data *data, const char **av);

#endif
