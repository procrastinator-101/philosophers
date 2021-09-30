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
    {
        ft_status_print(data, nb, data->time_begin, DIED);
        exit(END_DEAD);
    }
    return ((nb + 1) % data->attr->nb_philosophers);
}

static void ft_take_forks(t_data *data, int nb, int partner)
{
    sem_wait(data->philosophers[nb].lock.key);
    ft_status_print(data, nb, data->time_begin, "has taken a fork");
    sem_wait(data->philosophers[partner].lock.key);
    ft_status_print(data, nb, data->time_begin, "has taken a fork");
}

static void ft_eat(t_data *data, int nb, int partner)
{
    ft_take_forks(data, nb, partner);
    sem_wait(data->philosophers[nb].status_lock.key);
    data->philosophers[nb].iseating = 1;
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    sem_post(data->philosophers[nb].status_lock.key);
    ft_status_print(data, nb, data->time_begin, "is eating");
    ft_usleep(data->attr->time_to_eat * 1000);
    sem_post(data->philosophers[nb].lock.key);
    sem_post(data->philosophers[partner].lock.key);
    sem_wait(data->philosophers[nb].status_lock.key);
    data->philosophers[nb].iseating = 0;
    data->philosophers[nb].nb_meals++;
    sem_post(data->philosophers[nb].status_lock.key);
}

static void  ft_dine(t_data *data, int nb, int partner)
{
    while (data->attr->nb_meals < 0 || data->philosophers[nb].nb_meals < data->attr->nb_meals)
    {
        ft_eat(data, nb, partner);
        ft_status_print(data, nb, data->time_begin, "is sleeping");
        ft_usleep(data->attr->time_to_sleep * 1000);
        ft_status_print(data, nb, data->time_begin, "is thinking");
    }
}

void    *ft_simulate(void *arg)
{
    int         nb;
    int         partner;
    t_data      *data;

    data = ((t_philosopher *)arg)->data;
    nb = ((t_philosopher *)arg)->nb;
    pthread_detach(data->philosophers[nb].tid);
    partner = ft_getpartner(data, nb);
    sem_wait(data->philosophers[nb].status_lock.key);
    data->philosophers[nb].iseating = 0;
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    sem_post(data->philosophers[nb].status_lock.key);
    if (nb % 2)
        ft_usleep(SETUP_TIME);
    ft_dine(data, nb, partner);
    return (0);
}