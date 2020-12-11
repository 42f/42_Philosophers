/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_action_handlers.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/11 19:13:35 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_state		think_action_handler(t_data *data, const int philo_id)
{
	// data->philo_state[philo_id] = thinking_state;
	// data->philo_state_time_stamp[philo_id] = get_current_time();
	// usleep(1);
	(void)data;
	(void)philo_id;
	return (thinking_state);
}

t_state		take_forks_and_eat_action_handler(t_data *data, const int philo_id)
{
	acquire_forks(data, philo_id);
	data->philo_state[philo_id] = eating_state;
	data->philo_state_time_stamp[philo_id] = get_current_time();
	update_last_meal(data, philo_id);
	usleep(data->param[T_TO_EAT]);
	drop_forks(data, philo_id);
	data->nb_meals_eaten[philo_id]++;
	if (data->param[NB_MEALS] != UNSET
				&& data->nb_meals_eaten[philo_id] >= data->param[NB_MEALS])
		return (done_eating_state);
	return (finished_meal_state);
}

t_state		sleep_action_handler(t_data *data, const int philo_id)
{
	data->philo_state[philo_id] = sleeping_state;
	data->philo_state_time_stamp[philo_id] = get_current_time();
	usleep(data->param[T_TO_SLEEP]);
	data->philo_state[philo_id] = thinking_state;
	data->philo_state_time_stamp[philo_id] = get_current_time();
	return (sleeping_state);
}

void		done_eating_action_handler(t_data *data, const int philo_id)
{
	data->done_report_flag[philo_id] = true;
	data->first_done_report = true;
}
