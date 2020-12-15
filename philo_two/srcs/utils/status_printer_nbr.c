/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer_nbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:03 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/15 17:11:41 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		ft_fill(char *buffer, unsigned long n_val)
{
	if (n_val >= 10)
		ft_fill(buffer - 1, n_val / 10);
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

int				ft_putnbr(int fd, unsigned long nb)
{
	static char		buffer[BUFF_SIZE];
	size_t			len;

	memset(buffer, '\0', BUFF_SIZE);
	len = ft_itoa(nb, buffer);
	buffer[len] = ' ';
	return(write(fd, buffer, len + 1));
}
