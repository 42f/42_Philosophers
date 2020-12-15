/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:03 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/15 17:10:49 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t			len;

	len = 0;
	while (str != NULL && str[len] != '\0')
		len++;
	return (len);
}

int				ft_put_str_fd(int fd, const char *str)
{
	if (str != NULL)
		return (write(fd, str, ft_strlen(str)));
	return (0);
}

int				ft_put_message_fd(int fd, const size_t len, const char *str)
{
	if (str != NULL)
		return (write(fd, str, len));
	return (0);
}
