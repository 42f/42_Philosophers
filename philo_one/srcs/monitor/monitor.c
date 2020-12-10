/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:04 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/10 09:37:28 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static bool		loop_condition(t_data *data, int philo_id, t_state state)
{
	return (state != dead_state && data->death_report_flag == false
	&& data->done_report_flag[philo_id] == false);
}

void			*philo_monitor(void *i_arg)
{
	int				philo_id;
	t_data			*data;
	t_state			state;

	data = get_data(GET);
	philo_id = *((int *)i_arg);
	state = startup_state;
	while (loop_condition(data, philo_id, state) == true)
	{
		usleep(1);
		state = check_aliveness(data, philo_id, state);
	}
	if (data->done_report_flag[philo_id] == false && state == dead_state)
		put_death_status(data, philo_id);
	pthread_exit(NULL);
}
