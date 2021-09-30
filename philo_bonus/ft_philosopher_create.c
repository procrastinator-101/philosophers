/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 00:24:28 by youness           #+#    #+#             */
/*   Updated: 2021/09/30 00:24:29 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  ft_create_philosem(t_philosopher *philosopher)
{
    int ret;

    ret = ft_semcreate(&(philosopher->lock), PLOCK, philosopher->nb, 1);
    if (ret)
        return (ret);
    ret = ft_semcreate(&(philosopher->status_lock), PSLOCK, philosopher->nb, 1);
    if (ret)
    {
        ft_semdel(&(philosopher->lock));
        return (ret);
    }
    return (0);
}

t_philosopher   *ft_philosopher_create(int nb, t_data *data, int *error)
{
    int             ret;
    t_philosopher   *philosopher;

    *error = EMAF;
    philosopher = malloc(sizeof(t_philosopher));
    if (!philosopher)
        return (0);
    philosopher->data = data;
    philosopher->iseating = 1;
    philosopher->nb = nb;
    philosopher->nb_meals = 0;
    *error = ft_create_philosem(philosopher);
    if (!*error)
        return (philosopher);
    free(philosopher);
    return (0);
}