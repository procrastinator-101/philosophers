/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialise_locks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:46:09 by youness           #+#    #+#             */
/*   Updated: 2021/10/17 19:48:42 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_initialise_status_locks(t_data *data)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < data->attr->nb_philosophers)
	{
		ret = ft_semcreate(&(data->philosophers[i].status_lock), PSLOCK, i, 1);
		if (ret)
		{
			ft_semaphore_clear(data, 1, data->attr->nb_philosophers, i);
			return (ret);
		}
	}
	return (0);
}

static int	ft_initialise_philosopher_locks(t_data *data)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < data->attr->nb_philosophers)
	{
		ret = ft_semcreate(&(data->philosophers[i].lock), PLOCK, i, 1);
		if (ret)
		{
			ft_semaphore_clear(data, 1, i, 0);
			return (ret);
		}
	}
	return (ft_initialise_status_locks(data));
}

int	ft_initialise_locks(t_data *data)
{
	int	i;
	int	ret;

	ret = ft_semcreate(&(data->lock), MLOCK, -1, 1);
	if (ret)
		return (ret);
	ret = ft_semcreate(&(data->display_lock), MDLOCK, -1, 1);
	if (ret)
	{
		ft_semdel(&(data->lock));
		return (ret);
	}
	i = -1;
	while (++i < data->attr->nb_philosophers)
	{
		data->philosophers[i].nb = i;
		data->philosophers[i].data = data;
		data->philosophers[i].iseating = 1;
		data->philosophers[i].nb_meals = 0;
	}
	return (ft_initialise_philosopher_locks(data));
}
