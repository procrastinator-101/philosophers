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
        kill(data->philosophers[i]->pid, SIGKILL);
}

static void ft_clean_foreign_philos(t_data *data, int nb, int partner)
{
    int i;

    i = -1;
    while (++i < data->attr.nb_philosophers)
    {
        if (i == nb || i == partner)
            continue ;
        ft_philosopher_del(data->philosophers[i]);
    }
    free(data->philosophers);
}

static int  ft_create_childs(t_data *data, int nb)
{
    int             partner;
    t_philosopher   *philosopher;

    data->philosophers[nb]->pid = fork();
    if (data->philosophers[nb]->pid == -1)
        return (EPCF);
    if (data->philosophers[nb]->pid)
        return (0);
    philosopher = data->philosophers[nb];
    partner = (nb + 1) % data->attr.nb_philosophers;
    philosopher->partner = data->philosophers[partner];
    ft_clean_unecessary_data(data, partner);
    return (0);
}

int    ft_launch_simulation(t_data *data)
{
   int  i;
   int  ret;

   i = -1;
   while (++i < data->attr.nb_philosophers)
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
