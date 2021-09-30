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

# include <pthread.h>
# include <sys/time.h>

# include <sys/types.h>
# include <signal.h>

# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define EIARG  1       //ERROR INVALID ARGUMENT
# define EMARG  2       //ERROR MISSING ARGUMENT(S)
# define EMAF   3       //ERROR MEMORY ALLOCATION FAILURE
# define ETCF   4       //ERROR THREAD CREATION FAILURE
# define ESCF   5       //ERROR SEMAPHORE CREATION FAILURE
# define ETAC   6       //ERROR TRUNCATED ARGUMENT CHARACTERS
# define EPCF   7       //ERROR PROCESS CREATION FAILURE

# define MAX_USLEEP 1000000
# define SETUP_TIME 10000

/*
# define M1 0X1
# define M2 0X10
# define M3 0X100
*/

# define DIED   "\t\t\t\t\tdied"

typedef struct timeval t_timeval;

typedef struct s_attr
{
    int                     nb_philosophers;
    unsigned                time_to_die;
    unsigned                time_to_eat;
    unsigned                time_to_sleep;
    int                     nb_meals;
}                           t_attr;

typedef struct s_semaphore
{
    char                    *name;
    sem_t                   *key;
}                           t_semaphore;

typedef struct s_philosopher
{
    int                     nb;
    int                     pid;
    int                     iseating;
    int                     nb_meals;
    void                    *data;
    t_semaphore             lock;
    t_semaphore             status_lock;
    t_timeval               last_meal;
    t_timeval               time_begin;
    struct s_philosopher    *partner;
}                           t_philosopher;

typedef struct s_data
{
    t_attr                  attr;
    t_semaphore             lock;
    t_semaphore             display_lock;
    t_philosopher           **philosophers;
}                           t_data;

void        ft_attr_print(t_attr *attr);
void        ft_status_print(t_data *data, int nb, t_timeval start, char *action);

t_data      *ft_getdata(int argc, char **argv, int *error);

int         ft_initialise_locks(t_data *data);

int         ft_launch_simulation(t_data *data);
int         ft_prepare_simulation(t_data **data, int argc, char **argv);

void        *ft_simulate(void *arg);
void        ft_supervise_simulation(t_data *data);

void        ft_cleanup(t_data *data);
void        ft_destroy_data(t_data *data);

void        ft_mutex_clear(t_data *data, int major, int locks, int status_locks);

/*-----------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------*/

# define MLOCK  "philo_bonus_lock"
# define MDLOCK "philo_bonus_display_lock"
# define PLOCK  "philo_bonus_lock_"
# define PSLOCK "philo_bonus_status_lock_"

void    ft_semdel(t_semaphore *semaphore);
void    ft_semclear(t_data *data, int major, int locks, int status_locks);
int     ft_semcreate(t_semaphore *semaphore, char *type, int id, int value);

void    ft_philosopher_del(t_philosopher *philosopher);
void    ft_philosopher_nclear(t_philosopher **philosophers, int n);
t_philosopher   *ft_philosopher_create(int nb, t_data *data, int *error);

/*-----------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------*/



void        ft_manage_error(int error);

int	        ft_strcmp(const char *s1, const char *s2);
void        ft_usleep(useconds_t usec);
void	    ft_putstr_fd(char *s, int fd);
unsigned    ft_gettimestamp(t_timeval start);
unsigned    ft_atou_check(const char *str, int *error);

#endif
