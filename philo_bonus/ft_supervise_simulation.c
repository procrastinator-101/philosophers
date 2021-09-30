/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supervise_simulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:21:16 by youness           #+#    #+#             */
/*   Updated: 2021/09/28 15:21:17 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_update_child_status(t_data *data, int pid)
{
    int i;

    i = -1;
    while (++i < data->attr->nb_philosophers)
    {
        if (pid == data->philosophers[i].pid)
        {
            data->philosophers[i].alive = 0;
            return ;
        }
    }
}

void    ft_supervise_simulation(t_data *data)
{
    int ret;
    int pid;
    int alive;
    int status;

    alive = data->attr->nb_philosophers;
    while (alive-- > 0)
    {
        pid = waitpid(-1, &status, 0);
        ft_update_child_status(data, pid);//pid = -1 -> foreign
        if (WIFEXITED(status))
        {
            ret =  WEXITSTATUS(status);
            if (ret == END_DEAD || ret == END_ERROR)
            {
                ft_kill_alive_childs(data, pid);
                break ;
            }
        }
        else if (WIFSIGNALED(status))
        {
            ft_kill_alive_childs(data, pid);
            break ;
        }
    }
    ft_cleanup(data);
}
