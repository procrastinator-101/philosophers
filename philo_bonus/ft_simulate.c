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

static void ft_eat(t_data *data, int nb)
{
    sem_wait(data->lock.key);
    ft_status_print(data, nb, data->time_begin, "has taken a fork");
    sem_wait(data->lock.key);
    sem_wait(data->philosophers[nb].status_lock.key);
    ft_status_print(data, nb, data->time_begin, "has taken a fork");
    data->philosophers[nb].iseating = 1;
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    sem_post(data->philosophers[nb].status_lock.key);
    ft_status_print(data, nb, data->time_begin, "is eating");
    ft_usleep(data->attr->time_to_eat * 1000);
    sem_post(data->lock.key);
    sem_post(data->lock.key);
    sem_wait(data->philosophers[nb].status_lock.key);
    data->philosophers[nb].iseating = 0;
    data->philosophers[nb].nb_meals++;
    sem_post(data->philosophers[nb].status_lock.key);
}

static void  ft_dine(t_data *data, int nb)
{
    while (data->attr->nb_meals < 0 || data->philosophers[nb].nb_meals < data->attr->nb_meals)
    {
        ft_eat(data, nb);
        sem_wait(data->philosophers[nb].status_lock.key);
        ft_status_print(data, nb, data->time_begin, "is sleeping");
        sem_post(data->philosophers[nb].status_lock.key);
        ft_usleep(data->attr->time_to_sleep * 1000);
        sem_wait(data->philosophers[nb].status_lock.key);
        ft_status_print(data, nb, data->time_begin, "is thinking");
        sem_post(data->philosophers[nb].status_lock.key);
    }
}

void    *ft_simulate(void *arg)
{
    int         nb;
    t_data      *data;

    data = ((t_philosopher *)arg)->data;
    nb = ((t_philosopher *)arg)->nb;
    pthread_detach(data->philosophers[nb].tid);
    sem_wait(data->philosophers[nb].status_lock.key);
    data->philosophers[nb].iseating = 0;
    gettimeofday(&(data->philosophers[nb].last_meal), 0);
    sem_post(data->philosophers[nb].status_lock.key);
    if (nb % 2)
        ft_usleep(SETUP_TIME);
    ft_dine(data, nb);
    return (0);
}