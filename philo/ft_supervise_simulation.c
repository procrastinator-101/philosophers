/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supervise_simulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:21:16 by youness           #+#    #+#             */
/*   Updated: 2021/09/28 15:21:17 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_supervise_simulation(t_data *data)
{
    int i;
    int isfull;

    isfull = 0;
    while (!data->isdead && !isfull)
    {
        i = -1;
        isfull = 1;
        while (++i < data->attr->nb_philosophers && !data->isdead)
        {
            pthread_mutex_lock(&(data->philosophers[i].status_lock));
            if (data->attr->nb_meals < 0 || data->philosophers[i].nb_meals < data->attr->nb_meals)
            {
                if (!data->philosophers[i].iseating && ft_gettimestamp(data->philosophers[i].last_meal) >= data->attr->time_to_die)
                    ft_status_print(data, i, data->time_begin, DIED);
                else
                    isfull = 0;
            }
            pthread_mutex_unlock(&(data->philosophers[i].status_lock));
        }
    }
}
