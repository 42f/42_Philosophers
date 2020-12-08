#include "philo_one.h"

static size_t		ft_strlen(const char *str)
{
	size_t		len;

	len = 0;
	while (str != NULL && str[len] != '\0')
		len++;
	return (len);
}

void	ft_put_str_fd(int fd, const char *s)
{
	write(fd, s, ft_strlen(s));
}

static char	*ft_fill(char *r, unsigned long n_val, int i)
{
	if (n_val != 0)
	{
		r[i] = ' ';
		i--;
		while (n_val > 0 && i >= 0)
		{
			r[i] = (n_val % 10) + '0';
			n_val = n_val / 10;
			i--;
		}
	}
	else
	{
		r[0] = '0';
		r[1] = ' ';
	}
	return (r);
}

char		*ft_itoa(unsigned long nb)
{
	char			*ret;
	int				len;
	unsigned long	nb_val;

	len = 0;
	nb_val = nb;
	while (nb_val != 0)
	{
		nb_val = nb_val / 10;
		len++;
	}
	ret = (char *)malloc((len + 2) * sizeof(char));
	memset(ret, '\0', (len + 2) * sizeof(char));
	if (ret == NULL)
		exit (1);							// failure routine
	return (ft_fill(ret, nb, len));
}

void		ft_putnbr(unsigned long n)
{
	char	*nb;

	nb = ft_itoa(n);
	ft_put_str_fd(STDOUT_FILENO, nb);
	free(nb);
}

t_data	*get_data(t_data *mem)
{
	static t_data	*mem_backup = NULL;

	if (mem != GET)
		mem_backup = mem;
	return (mem_backup);
}
