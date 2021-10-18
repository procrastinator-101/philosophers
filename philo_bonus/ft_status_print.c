/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 15:16:12 by youness           #+#    #+#             */
/*   Updated: 2021/10/18 15:10:36 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_status_print(t_data *data, int nb, t_timeval start, char *action)
{
	sem_wait(data->display_lock.key);
	printf("%ld  philosopher %d  %s\n", ft_gettimestamp(start), nb + 1, action);
	if (ft_strcmp(action, DIED))
		sem_post(data->display_lock.key);
}
