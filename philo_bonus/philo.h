/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:25:00 by youness           #+#    #+#             */
/*   Updated: 2021/10/18 16:22:21 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# include <pthread.h>
# include <sys/time.h>

# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>

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

# define MLOCK  "philo_bonus_lock"
# define LLOCK  "philo_bonus_launch_lock"
# define MDLOCK "philo_bonus_display_lock"
# define PLOCK  "philo_bonus_lock_"
# define PSLOCK "philo_bonus_status_lock_"

# define MAX_USLEEP		1000000

# define RESTTIME		100
# define SETUP_TIME		50000
# define CREATE_TIME	10000

# define MARGIN			20

# define END_FULL	0
# define END_DEAD	1
# define END_ERROR	2

# define DIED	"\t\t\t\t\tdied"

typedef struct timeval	t_timeval;

typedef struct s_attr
{
	int	nb_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
}		t_attr;

typedef struct s_semaphore
{
	char	*name;
	sem_t	*key;
}			t_semaphore;

typedef struct s_philosopher
{
	int				nb;
	int				pid;
	int				alive;
	int				iseating;
	int				nb_meals;
	pthread_t		tid;
	void			*data;
	t_timeval		last_meal;
	t_semaphore		status_lock;
}					t_philosopher;

typedef struct s_data
{
	t_timeval		time_begin;
	t_semaphore		lock;
	t_semaphore		launch_lock;
	t_semaphore		display_lock;
	t_attr			*attr;
	t_philosopher	*philosophers;
}					t_data;

void			ft_status_print(t_data *data, int nb, t_timeval start, \
				char *action);

t_data			*ft_getdata(int argc, char **argv, int *error);

int				ft_initialise_locks(t_data *data);

int				ft_launch_simulation(t_data *data);
int				ft_prepare_simulation(t_data **data, int argc, char **argv);

void			*ft_simulate(void *arg);

void			ft_cleanup(t_data *data);
void			ft_destroy_data(t_data *data);

void			ft_semdel(t_semaphore *semaphore);
void			ft_semclear(t_data *data, int major, int status_locks);
int				ft_semcreate(t_semaphore *semaphore, char *type, int id, \
				int value);

void			ft_supervise_philosopher(t_data *data, int nb);
void			ft_supervise_simulation(t_data *data);

char			*ft_itoa(int n);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);

long int		ft_gettimestamp(t_timeval start);

void			ft_manage_error(int error);

int				ft_strcmp(const char *s1, const char *s2);
void			ft_usleep(useconds_t usec);
void			ft_putstr_fd(char *s, int fd);
int				ft_atoi_check(const char *str, int *error);

#endif
