/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher_del.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 00:44:18 by youness           #+#    #+#             */
/*   Updated: 2021/10/17 19:45:48 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philosopher_del(t_philosopher *philosopher)
{
	ft_semdel(&(philosopher->lock));
	ft_semdel(&(philosopher->status_lock));
	free(philosopher);
}
