/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher_nclear.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 00:44:33 by youness           #+#    #+#             */
/*   Updated: 2021/09/30 00:44:36 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_philosopher_nclear(t_philosopher **philosophers, int n)
{
    int i;

    i = -1;
    while (++i < n)
        ft_philosopher_del(philosophers[i]);
    free(philosophers);
}