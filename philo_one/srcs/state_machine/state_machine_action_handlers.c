/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_action_handlers.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/14 18:00:23 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static bool	is_nb_meals_reached(t_data *data, const int philo_id)
{
	return (data->param[NB_MEALS] != UNSET
				&& data->nb_meals_eaten[philo_id] >= data->param[NB_MEALS]);
}

static bool	is_done_eating(t_data *data, int philo_id)
{
	unsigned long	time_to_eat;

	time_to_eat = (unsigned long)data->param[T_TO_EAT] / 1000;
	return (get_current_time() - data->last_meal[philo_id] >= time_to_eat
			|| data->first_done_report == true
			|| data->first_death_report == true);
}

t_state		take_forks_and_eat_action_handler(t_data *data, const int philo_id)
{
	acquire_forks(data, philo_id);
	if (data->first_death_report == true)
	{
		drop_forks(data, philo_id);
		return (finished_meal_state);
	}
	data->last_meal[philo_id] = get_current_time();
	data->philo_state_time_stamp[philo_id] = data->last_meal[philo_id];
	put_regular_status(data, philo_id, LEN_IS_EATING, MESSAGE_IS_EATING);
	while (is_done_eating(data, philo_id) == false)
		usleep(100);
	drop_forks(data, philo_id);
	data->nb_meals_eaten[philo_id]++;
	if (is_nb_meals_reached(data, philo_id) == true)
		return (reached_meals_nb_state);
	else
		return (finished_meal_state);
}

static bool	is_done_sleeping(t_data *data, unsigned long fell_asleep_timestamp)
{
	unsigned long	time_to_sleep;

	time_to_sleep = (unsigned long)data->param[T_TO_SLEEP] / 1000;
	return (get_current_time() - fell_asleep_timestamp >= time_to_sleep
			|| data->first_done_report == true
			|| data->first_death_report == true);
}

t_state		sleep_action_handler(t_data *data, const int philo_id)
{
	unsigned long	fell_asleep_timestamp;

	data->philo_state_time_stamp[philo_id] = get_current_time();
	put_regular_status(data, philo_id, LEN_IS_SLEEPING, MESSAGE_IS_SLEEPING);
	fell_asleep_timestamp = get_current_time();
	while (is_done_sleeping(data, fell_asleep_timestamp) == false)
		usleep(100);
	data->philo_state_time_stamp[philo_id] = get_current_time();
	put_regular_status(data, philo_id, LEN_IS_THINKING, MESSAGE_IS_THINKING);
	return (thinking_state);
}

void		done_eating_action_handler(t_data *data, const int philo_id)
{
	data->done_report_flag[philo_id] = true;
	data->first_done_report = true;
}
