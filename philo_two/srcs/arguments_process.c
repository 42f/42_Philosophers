/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:05 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/18 08:47:48 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*get_skipped_input(const char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return (str);
}

static int			ft_atoi(const char *str)
{
	int		output;
	size_t	i;

	output = 0;
	i = 0;
	str = get_skipped_input(str);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		output = output * 10 + (str[i++] - 48);
	return (str[0] == '-' ? -output : output);
}

static void			convert_from_msec_to_usec(int *nb)
{
	*nb *= 1000;
}

int					process_arguments(t_data *data, const char **av)
{
	int		arg_i;
	int		i;

	memset(data->param, 0, sizeof(data->param));
	data->param[NB_MEALS] = UNSET;
	i = 0;
	arg_i = i + 1;
	while (av != NULL && av[arg_i] != NULL && i < NB_OF_PARAM)
	{
		data->param[i] = ft_atoi(av[arg_i]);
		if (data->param[i] <= 0)
			return (FAILURE);
		i++;
		arg_i++;
	}
	if (data->param[NB_PHILO] > 200)
		return (FAILURE);
	convert_from_msec_to_usec(&data->param[T_TO_EAT]);
	convert_from_msec_to_usec(&data->param[T_TO_SLEEP]);
	return (SUCCESS);
}
