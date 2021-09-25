/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:18:14 by youness           #+#    #+#             */
/*   Updated: 2021/09/25 16:18:16 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_prepare_simulation(t_data *data)
{
    int i;
    int ret;

    data->isdead = 0;
    data->current = 0;
    ret = pthread_mutex_init(&(data->key), 0);
    if (ret)
        return (EMIF);
    i = -1;
    while (++i < data->attr->nb_philosophers)
    {
        data->philosophers[i].nb = i;
        ret = pthread_mutex_init(&(data->philosophers[i].key), 0);
        if (ret)
        {
            pthread_mutex_destroy(&(data->key));
            ft_mutex_nclear(data, i);
            return (EMIF);
        }
    }
    gettimeofday(&(data->time_begin), 0);
    return (0);
}