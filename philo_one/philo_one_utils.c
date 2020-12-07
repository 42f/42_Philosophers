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
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

static void	ft_writenbr(unsigned int c)
{
	c += '0';
	write(1, &c, 1);
}

void		ft_putnbr(unsigned int n)
{

	if (n >= 10)
		ft_putnbr(n / 10);
	ft_writenbr(n % 10);
}

t_data	*get_data(t_data *mem)
{
	static t_data	*mem_backup = NULL;

	if (mem != GET)
		mem_backup = mem;
	return (mem_backup);
}
