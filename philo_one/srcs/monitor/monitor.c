/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:08:04 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 12:09:15 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static bool		loop_condition(t_data *data,int philo_id, t_state state)
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
	while(loop_condition(data, philo_id, state) == true)
	{
		state = check_aliveness(data, philo_id, state);
		usleep(1);
	}
	if (data->done_report_flag[philo_id] == false && state == dead_state)
		put_status(data, philo_id, MESSAGE_IS_DEAD);
	pthread_exit(NULL);
}
