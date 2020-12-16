/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:07:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/16 13:51:47 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			*philo_state_machine(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	state = startup_state;
	sem_wait(data->sem_race_starter);
	sem_post(data->sem_race_starter);
	while (data->first_death_report == false && state != reached_meals_nb_state)
	{
		if (state == thinking_state || state == startup_state)
			state = take_forks_and_eat_handler(data, philo_id);
		else if (state == finished_meal_state)
			state = sleep_and_think_handler(data, philo_id);
	}
	data->done_report_flag[philo_id] = true;
	sem_wait(data->sem_nb_philo_done);
	data->nb_philo_done++;
	sem_post(data->sem_nb_philo_done);
	return (NULL);
}
