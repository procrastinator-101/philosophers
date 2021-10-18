/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:11:10 by youness           #+#    #+#             */
/*   Updated: 2021/09/25 22:11:12 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_destroy_data(t_data *data)
{
    if (!data)
        return ;
    free(data->attr);
    free(data->philosophers);
    free(data);
}