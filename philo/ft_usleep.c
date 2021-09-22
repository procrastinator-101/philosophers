/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:45:40 by youness           #+#    #+#             */
/*   Updated: 2021/09/21 19:45:42 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_usleep(useconds_t usec)
{
    while (usec > MAX_USLEEP)
    {
        usleep(MAX_USLEEP - 1);
        usec -= MAX_USLEEP - 1;
    }
    usleep(usec);
}