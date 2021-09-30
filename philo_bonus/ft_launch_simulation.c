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

void    ft_supervise_philosopher(t_data *data, int nb)
{
    while (1)
    {
        sem_wait(data->philosophers[nb].status_lock.key);
        if (data->attr->nb_meals >= 0 && data->philosophers[nb].nb_meals >= data->attr->nb_meals)
            exit(END_FULL);
        if (!data->philosophers[nb].iseating && ft_gettimestamp(data->philosophers[nb].last_meal) >= data->attr->time_to_die)
        {
            ft_status_print(data, nb, data->time_begin, DIED);
            exit(END_DEAD);
        }
        sem_post(data->philosophers[nb].status_lock.key);
        ft_usleep(1000);
    }
}

void    ft_runchild(t_data *data, int idx)
{
    int         ret;

    if (data->attr->nb_philosophers == 1)
    {
        ft_status_print(data, idx, data->time_begin, DIED);
        exit(END_DEAD);
    }
    ret = pthread_create(&(data->philosophers[idx].tid), 0, ft_simulate, data->philosophers + idx);
    if (ret)
    {
        ft_manage_error(ETCF);
        exit(END_ERROR);
    }
    ft_supervise_philosopher(data, idx);
    exit(END_FULL);
}

static int  ft_create_childs(t_data *data, int idx)
{
    data->philosophers[idx].pid = fork();
    if (data->philosophers[idx].pid == -1)
        return (EPCF);
    if (data->philosophers[idx].pid)
        return (0);
    
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
