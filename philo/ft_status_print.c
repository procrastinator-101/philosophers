/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:16:12 by youness           #+#    #+#             */
/*   Updated: 2021/09/28 15:16:13 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_status_print(t_data *data, int nb, t_timeval start, char *action)
{
    pthread_mutex_lock(&(data->display_lock));
    printf("%u  philosopher %d  %s\n", ft_gettimestamp(start), nb + 1, action);
    pthread_mutex_unlock(&(data->display_lock));
}