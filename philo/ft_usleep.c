/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:45:40 by youness           #+#    #+#             */
/*   Updated: 2021/10/15 16:32:57 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(useconds_t usec)
{
	t_timeval	start;
	useconds_t	msec;

	gettimeofday(&start, 0);
	msec = usec / 1000;
	if (usec > MARGIN * 1000)
		usec -= MARGIN * 1000;
	else
		usec -= msec * 1000;
	while (usec > MAX_USLEEP - 1)
	{
		usleep(MAX_USLEEP - 1);
		usec -= MAX_USLEEP - 1;
	}
	if (usec > 0)
		usleep(usec);
	while (ft_gettimestamp(start) < (long)msec)
		;
}
