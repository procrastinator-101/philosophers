/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:25:00 by youness           #+#    #+#             */
/*   Updated: 2021/09/21 18:25:37 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <sys/time.h>

# include <pthread.h>

# define EIARG  1       //ERROR INVALID ARGUMENT
# define EMARG  2       //ERROR MISSING ARGUMENT(S)
# define EMAF   3       //ERROR MEMORY ALLOCATION FAILURE
# define ETCF   4       //ERROR THREAD CREATION FAILURE
# define EMIF   5       //ERROR MUTEX INITIALISATION FAILURE

# define MAX_USLEEP 1000000

typedef struct timeval t_timeval;


typedef struct s_attr
{
    int         nb_philosophers;
    unsigned    time_to_die;
    unsigned    time_to_eat;
    unsigned    time_to_sleep;
    int         nb_meals;
}               t_attr;

typedef struct s_philosopher
{
    unsigned        nb;
    pthread_t       id;
    pthread_mutex_t key;
    t_timeval       last_meal;
}                   t_philosopher;

typedef struct s_container
{
    t_attr          *attr;
    t_philosopher   *philosophers;
    t_timeval       time_begin;
    int             current;
    int             isdead;
}                   t_container;

void    *ft_simulate(void *arg);

void    ft_usleep(useconds_t usec);

void	ft_putstr_fd(char *s, int fd);
void        ft_manage_error(int error);
unsigned    ft_atou_check(const char *str, int *error);

#endif