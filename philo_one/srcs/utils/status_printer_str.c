/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printer_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:03 by bvalette          #+#    #+#             */
/*   Updated: 2020/12/15 16:25:36 by bvalette         ###   ########.fr       */
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

void			ft_put_message_fd(int fd, const size_t len, const char *str)
{
	if (str != NULL)
		write(fd, str, len);
}
