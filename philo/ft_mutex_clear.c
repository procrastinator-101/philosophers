/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:58:50 by youness           #+#    #+#             */
/*   Updated: 2021/09/26 19:58:52 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_mutex_clear(t_data *data, int major, int locks, int status_locks)
{
    int i;
    
    if (major)
    {
        pthread_mutex_destroy(&(data->lock));
        pthread_mutex_destroy(&(data->display_lock));
        pthread_mutex_destroy(&(data->launch_lock));
    }
    i = -1;
    while (++i < locks)
        pthread_mutex_destroy(&(data->philosophers[i].lock));
    i = -1;
    while (++i < status_locks)
        pthread_mutex_destroy(&(data->philosophers[i].status_lock));
}
