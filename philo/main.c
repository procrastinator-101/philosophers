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

void    ft_attr_print(t_attr *attr)
{
    printf("nb_philosophers = %u\n", attr->nb_philosophers);
    printf("time_to_die     = %u\n", attr->time_to_die);
    printf("time_to_eat     = %u\n", attr->time_to_eat);
    printf("time_to_sleep   = %u\n", attr->time_to_sleep);
    printf("nb_meals        = %d\n", attr->nb_meals);
}

void    ft_philosopher_print(t_philosopher *philosopher)
{
    printf("nb = %d\n", philosopher->nb);
    printf("id = %lu\n", philosopher->id);
    printf("time since last meal = %u\n", ft_gettimestamp(philosopher->last_meal));
}

void    ft_start_simulation(t_data *data)
{
    int i;
    int ret;

    i = -1;
    while (++i < data->attr->nb_philosophers)
    {
        ret = pthread_create(&(data->philosophers[i].id), 0, ft_simulate, data);
        if (ret)
            ft_manage_error(ETCF);
    }
}

void    ft_supervise(t_data *data)
{
    int i;
    int nb;

    nb = 0;
    while (!data->isdead)
    {
        i = -1;
        while (++i < data->attr->nb_philosophers && !data->isdead)
        {
            pthread_mutex_lock(&(data->philosophers[i].status_lock));
            if (!data->philosophers[i].iseating && ft_gettimestamp(data->philosophers[i].last_meal) >= data->attr->time_to_die)
            {
                data->isdead = 1;
                nb = i;
            }
            pthread_mutex_unlock(&(data->philosophers[i].status_lock));
        }
    }
    ft_status_print(data, nb, data->time_begin, "\t\t\t\t\tdied");
}

int main(int argc, char **argv)
{
    int     i;
    int     error;
    t_data  *data;

    error = ft_prepare_simulation(&data, argc, argv);
    if (error)
    {
        ft_manage_error(error);
        return (1);
    }
    //clean until here
    ft_start_simulation(data);
    ft_supervise(data);
    i = -1;
    while (++i < data->attr->nb_philosophers)
        pthread_join(data->philosophers[i].id, 0);
    ft_cleanup(data);
    return (0);
}