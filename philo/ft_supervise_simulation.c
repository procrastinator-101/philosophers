/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supervise_simulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:21:16 by youness           #+#    #+#             */
/*   Updated: 2021/10/15 16:43:14 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_death(t_data *data, int nb, int *isfull)
{
	if (data->isdead)
		return (1);
	if (data->attr->nb_meals < 0 || \
			data->philosophers[nb].nb_meals < data->attr->nb_meals)
	{
		if (!data->philosophers[nb].iseating && \
				ft_gettimestamp(data->philosophers[nb].last_meal) >= \
				(long)data->attr->time_to_die)
		{
			ft_status_print(data, nb, data->time_begin, DIED);
			return (1);
		}
		else
			*isfull = 0;
	}
	return (0);
}

void	ft_supervise_simulation(t_data *data)
{
	int	i;
	int	ret;
	int	isfull;

	isfull = 0;
	while (!isfull)
	{
		i = -1;
		isfull = 1;
		while (++i < data->attr->nb_philosophers)
		{
			pthread_mutex_lock(&(data->philosophers[i].status_lock));
			ret = ft_check_death(data, i, &isfull);
			pthread_mutex_unlock(&(data->philosophers[i].status_lock));
			if (ret)
				return ;
		}
	}
}
