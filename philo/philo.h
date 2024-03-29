/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:25:00 by youness           #+#    #+#             */
/*   Updated: 2021/10/15 16:31:39 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <sys/time.h>
# include <limits.h>

# include <pthread.h>

# define EIARG  1       //ERROR INVALID ARGUMENT
# define EMARG  2       //ERROR MISSING ARGUMENT(S)
# define EMAF   3       //ERROR MEMORY ALLOCATION FAILURE
# define ETCF   4       //ERROR THREAD CREATION FAILURE
# define EMIF   5       //ERROR MUTEX INITIALISATION FAILURE
# define ETAC   6       //ERROR TRUNCATED ARGUMENT CHARACTERS

# define MAX_USLEEP 1000000
# define SETUP_TIME 10000
# define MARGIN     20
# define RESTTIME	100

# define DIED   "\t\t\t\t\tdied" //to modify

typedef struct timeval	t_timeval;

typedef struct s_attr
{
	int	nb_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
}		t_attr;

typedef struct s_philosopher
{
	pthread_t		id;
	pthread_mutex_t	lock;
	pthread_mutex_t	status_lock;
	t_timeval		last_meal;
	void			*data;
	int				nb;
	int				iseating;
	int				nb_meals;
}					t_philosopher;

typedef struct s_data
{
	t_attr			*attr;
	t_philosopher	*philosophers;
	t_timeval		time_begin;
	pthread_mutex_t	lock;
	pthread_mutex_t	launch_lock;
	pthread_mutex_t	display_lock;
	int				isdead;
	int				count;
}					t_data;

void			ft_attr_print(t_attr *attr);
void			ft_status_print(t_data *data, int nb, t_timeval start, \
				char *action);

t_data			*ft_getdata(int argc, char **argv, int *error);

int				ft_initialise_locks(t_data *data);

int				ft_launch_simulation(t_data *data);
int				ft_prepare_simulation(t_data **data, int argc, char **argv);

void			*ft_simulate(void *arg);
void			ft_supervise_simulation(t_data *data);

void			ft_cleanup(t_data *data);
void			ft_destroy_data(t_data *data);

void			ft_mutex_clear(t_data *data, int major, int locks, \
				int status_locks);

void			ft_manage_error(int error);

int				ft_strcmp(const char *s1, const char *s2);
void			ft_usleep(useconds_t usec);
void			ft_putstr_fd(char *s, int fd);
long			ft_gettimestamp(t_timeval start);
int				ft_atoi_check(const char *str, int *error);

#endif
