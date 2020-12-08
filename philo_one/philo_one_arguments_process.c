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

	memset(data->param, 0, sizeof(data->param));
	i = 0;
	arg_i = i + 1;
	data->param[NB_MEALS] = UNSET;
	while (av != NULL && av[arg_i] != NULL && i < NB_OF_USEC_ARGS)
	{
		data->param[i] = ft_atoi(av[arg_i]);
		i++;
		arg_i++;
	}
	return (SUCCESS);
}
