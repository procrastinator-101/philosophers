/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettimestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:52:43 by youness           #+#    #+#             */
/*   Updated: 2021/10/15 16:50:22 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_gettimestamp(t_timeval start)
{
	long		timestamp;
	t_timeval	now;

	gettimeofday(&now, 0);
	timestamp = (now.tv_sec - start.tv_sec) * 1000000;
	timestamp = timestamp + now.tv_usec - start.tv_usec;
	return (timestamp / 1000);
}
