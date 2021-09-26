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

void    ft_status_print(t_data *data, int nb, t_timeval start, char *action)
{
    pthread_mutex_lock(&(data->display_key));
    printf("%u  philosopher %d  %s\n", ft_gettimestamp(start), nb + 1, action);
    pthread_mutex_unlock(&(data->display_key));
}

static int  ft_getpartner(int nb, int nb_philosophers)
{
    //more efficient
    //return ((nb + 1) % nb_philosophers);
    if (nb % 2)
        return (nb - 1);
    if (nb < nb_philosophers - 1)
        return (nb + 1);
    return (0);
}

static void ft_eat(t_data *data, int nb, int partner)
{
    pthread_mutex_lock(&(data->philosophers[nb].status_lock));
    data->philosophers[nb].iseating = 1;
    pthread_mutex_unlock(&(data->philosophers[nb].status_lock));
    ft_status_print(data, nb, data->time_begin, "has taken a fork");
    ft_status_print(data, nb, data->time_begin, "is eating");
    usleep(data->attr->time_to_eat * 1000);
    pthread_mutex_unlock(&(data->philosophers[nb].lock));
    pthread_mutex_unlock(&(data->philosophers[partner].lock));
    pthread_mutex_lock(&(data->philosophers[nb].status_lock));
    data->philosophers[nb].iseating = 0;
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    pthread_mutex_unlock(&(data->philosophers[nb].status_lock));
}

static int  ft_dine(t_data *data, int nb, int partner)
{
    //possible deadlock
    pthread_mutex_lock(&(data->philosophers[nb].lock));
    pthread_mutex_lock(&(data->philosophers[partner].lock));
    if (data->isdead)
    {   
        pthread_mutex_unlock(&(data->philosophers[nb].lock));
        pthread_mutex_unlock(&(data->philosophers[partner].lock));
        return (1);
    }
    ft_eat(data, nb, partner);
    if (data->isdead)
        return (1);
    ft_status_print(data, nb, data->time_begin, "is sleeping");
    usleep(data->attr->time_to_sleep * 1000);
    ft_status_print(data, nb, data->time_begin, "is thinking");
    return (0);
}


/*
** all threads should start executing at the same time; then pair numbered philos will sleep for 50ms to let others take advantage
*/

void    *ft_simulate(void *arg)
{
    int         nb;
    int         partner;
    t_data      *data;

    data = (t_data *)arg;
    pthread_mutex_lock(&(data->key));
    nb = data->current++;
    pthread_mutex_unlock(&(data->key));
    partner = ft_getpartner(nb, data->attr->nb_philosophers);
    if (partner == nb)
    {
        data->isdead = 1;
        return (0);
    }
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    while (!data->isdead)
    {
        if (ft_dine(data, nb, partner))
            break ;
    }
    ft_status_print(data, nb, data->time_begin, "\t\t\t\t\tleft");
    return (0);
}