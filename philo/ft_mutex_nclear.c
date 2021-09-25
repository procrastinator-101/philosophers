/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_nclear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:05:34 by youness           #+#    #+#             */
/*   Updated: 2021/09/25 23:05:36 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_mutex_nclear(t_data *data, int n)
{
    int i;
    
    i = -1;
    while (++i < n)
        pthread_mutex_destroy(&(data->philosophers[i].key));
}