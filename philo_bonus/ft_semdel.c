/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_semdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:24:17 by youness           #+#    #+#             */
/*   Updated: 2021/09/29 22:24:18 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_semdel(t_semaphore *semaphore)
{
    sem_close(semaphore->key);
    sem_unlink(semaphore->name);
    free(semaphore->name);
}