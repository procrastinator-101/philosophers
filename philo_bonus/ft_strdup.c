/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:25:20 by youness           #+#    #+#             */
/*   Updated: 2021/10/18 15:11:52 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s1[i])
		i++;
	ptr = (char *)malloc(i + 1);
	if (ptr == 0)
		return (0);
	ptr[i] = 0;
	while (--i >= 0)
		ptr[i] = s1[i];
	return (ptr);
}
