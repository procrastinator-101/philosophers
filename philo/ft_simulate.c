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

void    ft_status_print(int nb, t_timeval start, char *action)
{
    //it is better to use a mutex to avoid scrumbled output
    printf("%u  philosopher %d  %s\n", ft_gettimestamp(start), nb + 1, action);
}

static int  ft_getpartner(int nb, int nb_philosophers)
{
    if (nb % 2)
        return (nb - 1);
    if (nb < nb_philosophers - 1)
        return (nb + 1);
    return (0);
}

static int  ft_checkend_simulation(t_data *data, int nb, int partner)
{
    if (data->isdead)
    {   
        pthread_mutex_unlock(&(data->philosophers[nb].key));
        pthread_mutex_unlock(&(data->philosophers[partner].key));
        return (1);
    }
    if (ft_gettimestamp(data->philosophers[nb].last_meal) >= data->attr->time_to_die)
    {
        ft_status_print(nb, data->time_begin, "\t\t\t\t\tdied");
        pthread_mutex_unlock(&(data->philosophers[nb].key));
        pthread_mutex_unlock(&(data->philosophers[partner].key));
        data->isdead = 1;
        return (1);
    }
    return (0);
}

static int  ft_dine(t_data *data, int nb, int partner)
{
    pthread_mutex_lock(&(data->philosophers[nb].key));
    pthread_mutex_lock(&(data->philosophers[partner].key));
    if (ft_checkend_simulation(data, nb, partner))
        return (1);
    ft_status_print(nb, data->time_begin, "has taken a fork");
    ft_status_print(nb, data->time_begin, "is eating");
    usleep(data->attr->time_to_eat * 1000);
    //ft_usleep(data->attr->time_to_eat * 1000);
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    pthread_mutex_unlock(&(data->philosophers[nb].key));
    pthread_mutex_unlock(&(data->philosophers[partner].key));
    if (data->isdead)
        return (1);
    ft_status_print(nb, data->time_begin, "is sleeping");
    usleep(data->attr->time_to_sleep * 1000);
    //ft_usleep(data->attr->time_to_sleep * 1000);
    ft_status_print(nb, data->time_begin, "is thinking");
    return (0);
}

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
        ft_status_print(nb, data->time_begin, "\t\t\t\t\tdied");
        data->isdead = 1;
        return (0);
    }
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    while (!data->isdead)
    {
        if (ft_dine(data, nb, partner))
            break ;
    }
    return (0);
}