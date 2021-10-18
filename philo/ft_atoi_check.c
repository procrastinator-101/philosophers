/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:10:25 by youness           #+#    #+#             */
/*   Updated: 2021/10/15 16:54:50 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_check(const char *str, int *error)
{
	int			i;
	long int	ret;

	i = 0;
	*error = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+')
		i++;
	ret = 0;
	while (str[i] > 47 && str[i] < 58 && ret < (long)INT_MAX)
		ret = ret * 10 + (str[i++] - 48);
	if (str[i] || ret > (long)INT_MAX)
		*error = EIARG;
	return (ret);
}
