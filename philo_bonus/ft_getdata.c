/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:07:43 by youness           #+#    #+#             */
/*   Updated: 2021/10/15 16:52:06 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_getattr(t_attr *attr, int argc, char **argv)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (++i < argc)
	{
		if (i == 1)
			attr->nb_philosophers = ft_atou_check(argv[i], &error);
		else if (i == 2)
			attr->time_to_die = ft_atou_check(argv[i], &error);
		else if (i == 3)
			attr->time_to_eat = ft_atou_check(argv[i], &error);
		else if (i == 4)
			attr->time_to_sleep = ft_atou_check(argv[i], &error);
		else if (i == 5)
			attr->nb_meals = ft_atou_check(argv[i], &error);
		if (error)
			return (error);
	}
	if (argc < 6)
		attr->nb_meals = -1;
	return (0);
}

t_data	*ft_getdata(int argc, char **argv, int *error)
{
	t_data	*data;

	*error = EMAF;
	data = malloc(sizeof(t_data));
	if (!data)
		return (data);
	data->philosophers = 0;
	data->attr = malloc(sizeof(t_attr));
	if (!data->attr)
		return (data);
	*error = ft_getattr(data->attr, argc, argv);
	if (*error)
		return (data);
	data->philosophers = malloc(sizeof(t_philosopher) * \
		data->attr->nb_philosophers);
	if (!data->philosophers)
		*error = EMAF;
	return (data);
}
