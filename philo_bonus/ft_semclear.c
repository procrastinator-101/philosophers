/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_semclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:24:02 by youness           #+#    #+#             */
/*   Updated: 2021/10/18 16:22:03 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_semclear(t_data *data, int major, int status_locks)
{
	int	i;

	if (major)
	{
		ft_semdel(&(data->lock));
		ft_semdel(&(data->display_lock));
		ft_semdel(&(data->launch_lock));
	}
	i = -1;
	while (++i < status_locks)
		ft_semdel(&(data->philosophers[i].status_lock));
}
