/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:23:58 by youness           #+#    #+#             */
/*   Updated: 2021/09/21 18:24:05 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_getattr(t_attr *attr,  int argc, char **argv)
{
    int     i;
    int     error;

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
    printf("argc = %d\n", argc);
    if (argc < 6)
        attr->nb_meals = -1;
    return (0);
}

void    ft_print_attr(t_attr *attr)
{
    printf("nb_philosophers = %u\n", attr->nb_philosophers);
    printf("time_to_die     = %u\n", attr->time_to_die);
    printf("time_to_eat     = %u\n", attr->time_to_eat);
    printf("time_to_sleep   = %u\n", attr->time_to_sleep);
    printf("nb_meals        = %d\n", attr->nb_meals);
}

int main(int argc, char **argv)
{
    int             i;
    int             ret;
    t_attr          *attr;
    t_container     *args;
    t_philosopher   *philosophers;

    if (argc < 4)
        ft_manage_error(EMARG);
    attr = malloc(sizeof(t_attr));
    if (!attr)
        ft_manage_error(EMAF);
    ret = ft_getattr(attr, argc, argv);
    if (ret)
        ft_manage_error(ret);
    ft_print_attr(attr);
    args = malloc(sizeof(t_container));
    if (!args)
        ft_manage_error(EMAF);
    philosophers = malloc(sizeof(t_philosopher) * attr->nb_philosophers);
    if (!philosophers)
        ft_manage_error(EMAF);
    printf("ok\n");
    i = -1;
    while (++i < attr->nb_philosophers)
    {
        philosophers[i].nb = i;
        ret = pthread_mutex_init(&(philosophers[i].key), 0);
        if (ret)
            ft_manage_error(EMIF);
    }
    args->isdead = 0;
    args->attr = attr;
    args->philosophers = philosophers;
    i = -1;
    while (++i < attr->nb_philosophers)
        gettimeofday(&(philosophers[i].last_meal), 0);
    gettimeofday(&(args->time_begin), 0);
    i = -1;
    while (++i < attr->nb_philosophers)
    {
        args->current = i;
        ret = pthread_create(&(philosophers[i].id), 0, ft_simulate, args);
        if (ret)
            ft_manage_error(ETCF);
    }
    i = -1;
    while (++i < attr->nb_philosophers)
    {
        ret = pthread_join(philosophers[i].id, 0);
        if (!ret)
            exit(EXIT_SUCCESS);//should be done manually
    }
    return (0);
}