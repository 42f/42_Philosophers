/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_action_handlers.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/12 18:19:06 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static bool	is_nb_meals_reached(t_data *data, const int philo_id)
{
	return (data->param[NB_MEALS] != UNSET
				&& data->nb_meals_eaten[philo_id] >= data->param[NB_MEALS]);
}

t_state		take_forks_and_eat_action_handler(t_data *data, const int philo_id)
{
	acquire_forks(data, philo_id);
	if (data->first_death_report == true)
	{
		drop_forks(data, philo_id);
		return (finished_meal_state);
	}
	put_regular_status(data, philo_id, get_current_time(), MESSAGE_IS_EATING);
	usleep(data->param[T_TO_EAT]);
	drop_forks(data, philo_id);
	data->nb_meals_eaten[philo_id]++;
	if (is_nb_meals_reached(data, philo_id) == true)
		return (reached_meals_nb_state);
	else
		return (finished_meal_state);
}

t_state		sleep_action_handler(t_data *data, const int philo_id)
{
	put_regular_status(data, philo_id, get_current_time(), MESSAGE_IS_SLEEPING);
	usleep(data->param[T_TO_SLEEP]);
	put_regular_status(data, philo_id, get_current_time(), MESSAGE_IS_THINKING);
	return (thinking_state);
}

void		done_eating_action_handler(t_data *data, const int philo_id)
{
	data->done_report_flag[philo_id] = true;
	data->first_done_report = true;
}
