/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:58 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 17:10:05 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_arg(int argc, char **argv, t_struct *st)
{
	st->arg.nb_philo = ft_atoi(argv[1]);
	st->arg.time2die = ft_atoi(argv[2]);
	st->arg.time2eat = ft_atoi(argv[3]);
	st->arg.time2sleep = ft_atoi(argv[4]);
	st->arg.meals_to_eat = -1;
	if (argc == 6)
		st->arg.meals_to_eat = ft_atoi(argv[5]);
}

void	init_mutex(t_struct *st)
{
	pthread_mutex_init(&st->arg.mtx_print, NULL);
	pthread_mutex_init(&st->arg.mtx_dead, NULL);
	pthread_mutex_init(&st->arg.mtx_time_eat, NULL);
	pthread_mutex_init(&st->arg.mtx_finish, NULL);
}

int	init_philo(t_struct *st)
{
	int	i;

	i = 0;
	st->arg.time_start = actual_time();
	st->arg.flag = 0;
	st->arg.satiated_philos = 0;
	init_mutex(st);
	while (i < st->arg.nb_philo)
	{
		st->philo[i].id = i + 1;
		st->philo[i].last_eat = st->arg.time_start;
		st->philo[i].meals_eaten = 0;
		st->philo[i].finish = 0;
		st->philo[i].right_fork = NULL;
		pthread_mutex_init(&st->philo[i].left_fork, NULL);
		if (st->arg.nb_philo == 1)
			return (1);
		if (i == st->arg.nb_philo - 1)
			st->philo[i].right_fork = &st->philo[0].left_fork;
		else
			st->philo[i].right_fork = &st->philo[i + 1].left_fork;
		i++;
	}
	return (1);
}

void	free_all(t_struct *st)
{
	int	i;

	i = 0;
	while (st->arg.flag == 0)
		ft_usleep(1);
	while (i < st->arg.nb_philo)
	{
		pthread_join(st->philo[i].thread_id, NULL);
		i++;
	}
	pthread_mutex_destroy(&st->arg.mtx_print);
	i = 0;
	while (i < st->arg.nb_philo)
	{
		pthread_mutex_destroy(&st->philo[i].left_fork);
		i++;
	}
	free(st->philo);
}
