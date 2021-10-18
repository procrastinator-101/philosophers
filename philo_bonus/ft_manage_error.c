/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:06:09 by youness           #+#    #+#             */
/*   Updated: 2021/09/21 19:06:11 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_manage_error(int error)
{
    ft_putstr_fd("ERROR\n", STDERR_FILENO);
    if (error == EIARG)
        ft_putstr_fd("invalid argument\n", STDERR_FILENO);
    else if (error == EMARG)
        ft_putstr_fd("missing one or more arguments\n", STDERR_FILENO);
    else if (error == EMAF)
        ft_putstr_fd("memory allocation failure\n", STDERR_FILENO);
    else if (error == ETCF)
        ft_putstr_fd("thread creation failure\n", STDERR_FILENO);
    else if (error == ESCF)
        ft_putstr_fd("semaphore creation failure\n", STDERR_FILENO);
    else if (error == ETAC)
        ft_putstr_fd("truncated characters\n", STDERR_FILENO);
}