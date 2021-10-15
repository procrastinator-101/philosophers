/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:07:30 by youness           #+#    #+#             */
/*   Updated: 2021/10/15 16:49:05 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destroy_nthread(t_data *data, int n)
{
	int	i;

	data->isdead = 1;
	i = -1;
	while (++i < n)
		pthread_join(data->philosophers[i].id, 0);
}

static int	ft_create_threads(t_data *data)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < data->attr->nb_philosophers)
	{
		ret = pthread_create(&(data->philosophers[i].id), 0, ft_simulate, \
			data->philosophers + i);
		if (ret)
		{
			pthread_mutex_unlock(&(data->launch_lock));
			ft_destroy_nthread(data, i);
			return (ETCF);
		}
	}
	return (0);
}

int	ft_launch_simulation(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&(data->launch_lock));
	ret = ft_create_threads(data);
	if (ret)
		return (ret);
	ret = 1;
	while (ret)
	{
		ft_usleep(1000);
		pthread_mutex_lock(&(data->lock));
		if (data->count == data->attr->nb_philosophers)
			ret = 0;
		pthread_mutex_unlock(&(data->lock));
	}
	gettimeofday(&(data->time_begin), 0);
	pthread_mutex_unlock(&(data->launch_lock));
	return (0);
}
