# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youness <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 18:53:17 by youness           #+#    #+#              #
#    Updated: 2021/09/21 19:52:13 by youness          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR = younes

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=address

NAME = philo

SRC = ft_atoi_check.c \
	  ft_cleanup.c \
	  ft_destroy_data.c \
	  ft_getdata.c \
	  ft_gettimestamp.c \
	  ft_initialise_locks.c \
	  ft_launch_simulation.c \
	  ft_manage_error.c \
	  ft_mutex_clear.c \
	  ft_prepare_simulation.c \
	  ft_putstr_fd.c \
	  ft_simulate.c \
	  ft_status_print.c \
	  ft_strcmp.c \
	  ft_supervise_simulation.c \
	  ft_usleep.c \
	  main.c

OBJ = $(SRC:.c=.o)
HDR = philo.h

all: $(NAME)

$(NAME) : $(OBJ) $(HDR)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)

re: fclean all
