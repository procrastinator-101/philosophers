/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:51:23 by youness           #+#    #+#             */
/*   Updated: 2021/09/25 21:51:24 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_cleanup(t_data *data)
{
    pthread_mutex_destroy(&(data->key));
    ft_mutex_nclear(data, data->attr->nb_philosophers);
    ft_destroy_data(data);
}