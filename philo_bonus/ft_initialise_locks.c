/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialise_locks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:46:09 by youness           #+#    #+#             */
/*   Updated: 2021/10/18 15:19:49 by yarroubi         ###   ########.fr       */
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
			ft_semclear(data, 1, data->attr->nb_philosophers, i);
			return (ret);
		}
	}
	return (0);
}

int	ft_initialise_locks(t_data *data)
{
	int	ret;

	ret = ft_semcreate(&(data->lock), MLOCK, -1, data->attr->nb_philosophers);
	if (ret)
		return (ret);
	ret = ft_semcreate(&(data->display_lock), MDLOCK, -1, 1);
	if (ret)
	{
		ft_semdel(&(data->lock));
		return (ret);
	}
	ret = ft_semcreate(&(data->launch_lock), LLOCK, -1, 0);
	if (ret)
	{
		ft_semdel(&(data->lock));
		ft_semdel(&(data->display_lock));
		return (ret);
	}
	return (ft_initialise_status_locks(data));
}
