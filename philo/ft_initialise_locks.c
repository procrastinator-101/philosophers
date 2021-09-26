/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialise_locks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:46:09 by youness           #+#    #+#             */
/*   Updated: 2021/09/26 18:46:11 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  ft_initialise_status_locks(t_data *data)
{
    int i;
    int ret;

    i = -1;
    while (++i < data->attr->nb_philosophers)
    {
        ret = pthread_mutex_init(&(data->philosophers[i].status_lock), 0);
        if (ret)
        {
            ft_mutex_clear(data, M1 | M2, data->attr->nb_philosophers, i);
            return (EMIF);
        }
    }
    return (0);
}

static int  ft_initialise_philosopher_locks(t_data *data)
{
    int i;
    int ret;

    i = -1;
    while (++i < data->attr->nb_philosophers)
    {
        data->philosophers[i].nb = i;
        data->philosophers[i].iseating = 0;
        ret = pthread_mutex_init(&(data->philosophers[i].lock), 0);
        if (ret)
        {
            ft_mutex_clear(data, M1 | M2, i, 0);
            return (EMIF);
        }
    }
    return (ft_initialise_status_locks(data));
}

int ft_initialise_locks(t_data *data)
{
    int ret;

    ret = pthread_mutex_init(&(data->key), 0);
    if (ret)
        return (EMIF);
    ret = pthread_mutex_init(&(data->display_key), 0);
    if (ret)
    {
        pthread_mutex_destroy(&(data->key));
        return (EMIF);
    }
    return (ft_initialise_philosopher_locks(data));
}