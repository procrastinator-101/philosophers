/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_semcreate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:23:50 by youness           #+#    #+#             */
/*   Updated: 2021/10/17 19:44:24 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ft_getsemname(char *type, int id)
{
	char	*nb;
	char	*name;

	nb = ft_itoa(id);
	name = ft_strjoin(type, nb);
	free(nb);
	return (name);
}

int	ft_semcreate(t_semaphore *semaphore, char *type, int id, int value)
{
	if (id < 0)
		semaphore->name = ft_strdup(type);
	else
		semaphore->name = ft_getsemname(type, id);
	if (!semaphore->name)
		return (EMAF);
	sem_unlink(semaphore->name);
	semaphore->key = sem_open(semaphore->name, O_CREAT | O_RDWR, \
		S_IRWXU | S_IRWXG | S_IRWXO, value);
	if (semaphore->key != SEM_FAILED)
		return (0);
	free(semaphore->name);
	return (ESCF);
}
