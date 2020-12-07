#include "philo_one.h"

static int		is_digit_only(const char *av)
{
	int			i;

	i = 0;
	while (av != NULL && av[i] != '\0')
	{
		if ((av[i] < '0' || av[i] > '9') && (av[i] != '+' || av[i] != ' '))
			return (false);
		i++;
	}
	return (true);
}

static size_t		ft_strlen(const char *str)
{
	size_t		len;

	len = 0;
	while (str != NULL && str[len] != '\0')
		len++;
	return (len);
}

void				put_usage(void)
{
	write(STDERR_FILENO, USAGE0, ft_strlen(USAGE0));
	write(STDERR_FILENO, USAGE1, ft_strlen(USAGE1));
	write(STDERR_FILENO, USAGE2, ft_strlen(USAGE2));
}

int					check_arguments(const int ac, const char **av)
{
	int			i;

	if (ac < 5 || ac > 6)
		return (FAILURE);
	i = 1;
	while (av != NULL && av[i] != NULL)
	{
		if (is_digit_only(av[i]) == false)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
