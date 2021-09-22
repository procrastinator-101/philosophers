/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:51:41 by youness           #+#    #+#             */
/*   Updated: 2021/09/22 19:51:43 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned    ft_gettimestamp(t_timeval start)
{
    t_timeval           now;
    unsigned long long  timestamp;

    gettimeofday(&now, 0);
    timestamp = (now.tv_sec - start.tv_sec) * 1000000;
    timestamp = timestamp + now.tv_usec - start.tv_sec;
    return (timestamp);
}

void    ft_status_print(int nb, t_timeval start, char *action)
{
    //it is better to use a mutex to avoid scrumbled output
    printf("%u %d %s\n", ft_gettimestamp(start), nb, action);
}

void    *ft_simulate(void *arg)
{
    int         nb;
    int         partner;
    t_container *container;

    container = (t_container *)arg;
    nb = container->current;
    if (nb % 2)
        partner = nb - 1;
    else
        partner = nb + 1;
    while (ft_gettimestamp(container->philosophers[nb].last_meal) > container->attr->time_to_die && !container->isdead)
    {
        pthread_mutex_lock(&(container->philosophers[nb].key));
        pthread_mutex_lock(&(container->philosophers[partner].key));
        ft_status_print(nb, container->time_begin, "has taken a fork");
        ft_status_print(nb, container->time_begin, " is eating");
        usleep(container->attr->time_to_eat);
        gettimeofday(&(container->philosophers[nb].last_meal), 0);
        pthread_mutex_unlock(&(container->philosophers[nb].key));
        pthread_mutex_unlock(&(container->philosophers[partner].key));
        ft_status_print(nb, container->time_begin, "is sleeping");
        usleep(container->attr->time_to_sleep);
        ft_status_print(nb, container->time_begin, " is thinking");
    }
    ft_status_print(nb, container->time_begin, "died");
    container->isdead = 1;
    return (0);
}