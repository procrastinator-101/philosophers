/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:23:58 by youness           #+#    #+#             */
/*   Updated: 2021/09/21 18:24:05 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    int     i;
    int     error;
    t_data  *data;

    error = ft_prepare_simulation(&data, argc, argv);
    if (error)
    {
        ft_manage_error(error);
        return (EXIT_FAILURE);
    }
    error = ft_launch_simulation(data);
    if (error)
    {
        ft_cleanup(data);
        ft_manage_error(error);
        return (EXIT_FAILURE);
    }
    ft_supervise_simulation(data);
    i = -1;
    while (++i < data->attr->nb_philosophers)
        pthread_join(data->philosophers[i].id, 0);
    ft_cleanup(data);
    return (EXIT_SUCCESS);
}