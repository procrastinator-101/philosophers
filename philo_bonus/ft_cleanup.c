/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:51:23 by youness           #+#    #+#             */
/*   Updated: 2021/10/17 19:33:37 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_cleanup(t_data *data)
{
	int	nb;

	nb = data->attr->nb_philosophers;
	ft_semclear(data, 1, nb, nb);
	ft_destroy_data(data);
}
