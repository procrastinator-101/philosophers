/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supervise_simulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:21:16 by youness           #+#    #+#             */
/*   Updated: 2021/10/18 15:10:03 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_update_child_status(t_data *data, int pid)
{
	int	i;

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

static void	ft_kill_alive_childs(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->attr->nb_philosophers)
	{
		if (data->philosophers[i].alive)
			kill(data->philosophers[i].pid, SIGKILL);
	}
}

void	ft_supervise_simulation(t_data *data)
{
	int	ret;
	int	pid;
	int	alive;
	int	status;

	alive = data->attr->nb_philosophers;
	while (alive-- > 0)
	{
		pid = waitpid(-1, &status, 0);
		ft_update_child_status(data, pid);
		if (WIFEXITED(status))
		{
			ret = WEXITSTATUS(status);
			if (ret == END_DEAD || ret == END_ERROR)
			{
				ft_kill_alive_childs(data);
				break ;
			}
		}
		else if (WIFSIGNALED(status))
		{
			ft_kill_alive_childs(data);
			break ;
		}
	}
}
