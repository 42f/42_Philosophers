#include "philo_one.h"

static const char	*get_skipped_input(const char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return (str);
}

static int			ft_atoi(const char *str)
{
	int			output;
	size_t		i;

	output = 0;
	i = 0;
	str = get_skipped_input(str);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		output = output * 10 + (str[i++] - 48);
	return (str[0] == '-' ? -output : output);
}

int				process_arguments(t_data *data, const char **av)
{
	int			arg_i;
	int			i;

	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo <= 0)
		return (FAILURE);
	data->nb_forks = data->nb_philo;
	arg_i = 2;
	i = 0;
	while (av != NULL && av[arg_i] != NULL && i < NB_OF_USEC_ARGS)
	{
		data->param[i] = ft_atoi(av[arg_i]);
		i++;
		arg_i++;
	}
	if (av[arg_i] != NULL)
		data->nb_eat_turns = ft_atoi(av[arg_i]);
	else
		data->nb_eat_turns = UNSET;
	return (SUCCESS);
}
