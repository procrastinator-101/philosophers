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

static int  ft_getpartner(t_data *data, int nb)
{
    if (data->attr->nb_philosophers == 1)
        ft_status_print(data, nb, data->time_begin, DIED);
    return ((nb + 1) % data->attr->nb_philosophers);
}

static int  ft_take_forks(t_data *data, int nb, int partner)
{
    pthread_mutex_lock(&(data->philosophers[nb].lock));
    if (data->isdead)
    {   
        pthread_mutex_unlock(&(data->philosophers[nb].lock));
        return (0);
    }
    ft_status_print(data, nb, data->time_begin, "has taken a fork");
    pthread_mutex_lock(&(data->philosophers[partner].lock));
    if (data->isdead)
    {   
        pthread_mutex_unlock(&(data->philosophers[nb].lock));
        pthread_mutex_unlock(&(data->philosophers[partner].lock));
        return (0);
    }
    ft_status_print(data, nb, data->time_begin, "has taken a fork");
    return (1);
}

static void ft_eat(t_data *data, int nb, int partner)
{
    if (!ft_take_forks(data, nb, partner))
        return ;
    pthread_mutex_lock(&(data->philosophers[nb].status_lock));
    data->philosophers[nb].iseating = 1;
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    pthread_mutex_unlock(&(data->philosophers[nb].status_lock));
    ft_status_print(data, nb, data->time_begin, "is eating");
    ft_usleep(data->attr->time_to_eat * 1000);
    pthread_mutex_unlock(&(data->philosophers[nb].lock));
    pthread_mutex_unlock(&(data->philosophers[partner].lock));
    pthread_mutex_lock(&(data->philosophers[nb].status_lock));
    data->philosophers[nb].iseating = 0;
    data->philosophers[nb].nb_meals++;
    pthread_mutex_unlock(&(data->philosophers[nb].status_lock));
}

static void  ft_dine(t_data *data, int nb, int partner)
{
    while (!data->isdead)
    {
        if (data->attr->nb_meals >= 0 && data->philosophers[nb].nb_meals >= data->attr->nb_meals)
            return ;
        ft_eat(data, nb, partner);
        if (data->isdead)
            return ;
        ft_status_print(data, nb, data->time_begin, "is sleeping");
        ft_usleep(data->attr->time_to_sleep * 1000);
        if (data->isdead)
            return ;
        ft_status_print(data, nb, data->time_begin, "is thinking");
    }
}

void    *ft_simulate(void *arg)
{
    int         nb;
    int         partner;
    t_data      *data;

    data = ((t_philosopher *)arg)->data;
    pthread_mutex_lock(&(data->lock));
    data->count++;
    pthread_mutex_unlock(&(data->lock));
    pthread_mutex_lock(&(data->launch_lock));
    pthread_mutex_unlock(&(data->launch_lock));
    nb = ((t_philosopher *)arg)->nb;
    partner = ft_getpartner(data, nb);
    pthread_mutex_lock(&(data->philosophers[nb].status_lock));
    data->philosophers[nb].iseating = 0;
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    pthread_mutex_unlock(&(data->philosophers[nb].status_lock));
    if (nb % 2)
        ft_usleep(SETUP_TIME);
    ft_dine(data, nb, partner);
    return (0);
}