/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:03 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/13 09:47:44 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static size_t	ft_strlen(const char *str)
{
	size_t			len;

	len = 0;
	while (str != NULL && str[len] != '\0')
		len++;
	return (len);
}

void			ft_put_str_fd(int fd, const char *str)
{
	if (str != NULL)
		write(fd, str, ft_strlen(str));
}

void			ft_put_message_fd(int fd,  const size_t len, const char *str)
{
	if (str != NULL)
		write(fd, str, len);
}

static void		ft_fill(char *buffer, unsigned long n_val)
{
	if (n_val >= 10)
		ft_fill(buffer - 1, n_val / 10 );
	*buffer = (n_val % 10) + '0';
}

static size_t	ft_itoa(unsigned long nb, char buffer[BUFF_SIZE])
{
	size_t			len;
	unsigned long	nb_val;

	if (nb != 0)
	{
		len = 0;
		nb_val = nb;
		while (nb_val != 0)
		{
			nb_val = nb_val / 10;
			len++;
		}
		ft_fill(buffer + len - 1, nb);
		return (len);
	}
	else
	{
		buffer[0] = '0';
		return (1);
	}
}

void			ft_putnbr(int fd, unsigned long nb)
{
	static char		buffer[BUFF_SIZE];
	size_t			len;

	memset(buffer, '\0', BUFF_SIZE);
	len = ft_itoa(nb, buffer);
	buffer[len] = ' ';
	write(fd, buffer, len + 1);
}
