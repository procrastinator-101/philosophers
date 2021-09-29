/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:07:30 by youness           #+#    #+#             */
/*   Updated: 2021/09/28 15:07:32 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_destroy_nprocess(t_data *data, int n)
{
    int i;

    i = -1;
    while (++i < n)
        kill(data->philosophers[i].pid, SIGKILL);
}

static int  ft_create_childs(t_data *data, int idx)
{
    data->philosophers[idx].pid = fork();
    if (data->philosophers[idx].pid == -1)
        return (EPCF);
    if (data->philosophers[idx].pid)
        return (0);
    ft_clean_unecessary_data
    ft_simulate(data);
    return (0);
}

int    ft_launch_simulation(t_data *data)
{
   int  i;
   int  ret;

   i = -1;
   while (++i < data->attr->nb_philosophers)
   {
       ret = ft_create_childs(data, i);
       if (ret)
       {
           ft_destroy_nprocess(data, i);
           return (ret);
       }
   }
   return (0);
}
