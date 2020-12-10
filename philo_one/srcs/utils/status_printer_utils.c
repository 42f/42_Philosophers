/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:03 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/09 17:17:32 by bvalette         ###   ########.fr       */
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

void			ft_put_str_fd(int fd, const char *s)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

static char		*ft_fill(char *r, unsigned long n_val, int i)
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

static char		*ft_itoa(unsigned long nb)
{
	char			*ret;
	int				len;
	size_t			malloc_len;
	unsigned long	nb_val;

	len = 0;
	nb_val = nb;
	while (nb_val != 0)
	{
		nb_val = nb_val / 10;
		len++;
	}
	malloc_len = (nb_val > 0) ? len + 2 : len + 3;
	malloc_len *= sizeof(char);
	ret = (char *)malloc(malloc_len);
	if (ret != NULL)
	{
		memset(ret, '\0', malloc_len);
		return (ft_fill(ret, nb, len));
	}
	else
		return (NULL);
}

int				ft_putnbr(unsigned long n)
{
	char			*nb;

	nb = ft_itoa(n);
	if (nb != NULL)
	{
		ft_put_str_fd(STDOUT_FILENO, nb);
		free(nb);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}
