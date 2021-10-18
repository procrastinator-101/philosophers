/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:14:24 by youness           #+#    #+#             */
/*   Updated: 2021/10/18 15:19:19 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_getlen(int n)
{
	int	ret;

	ret = 1;
	while (n / 10)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ptr;

	len = ft_getlen(n) + (n < 0);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (ptr);
	ptr[len] = 0;
	if (n < 0)
		ptr[0] = '-';
	while (n)
	{
		len--;
		if (n < 0)
			ptr[len] = -(n % 10) + '0';
		else
			ptr[len] = n % 10 + '0';
		n /= 10;
	}
	return (ptr);
}
