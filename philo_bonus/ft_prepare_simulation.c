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

int ft_prepare_simulation(t_data **data, int argc, char **argv)
{
    int     error;

    if (argc < 5)
        return (EMARG);
    if (argc > 6)
        return (ETAC);
    *data = ft_getdata(argc, argv, &error);
    if (error)
    {
        ft_destroy_data(*data);
        return (error);
    }
    error = ft_initialise_locks(*data);
    if (error)
    {
        ft_destroy_data(*data);
        return (error);
    }
    (*data)->isdead = 0;
    return (0);
}