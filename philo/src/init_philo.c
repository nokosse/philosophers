/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:06:30 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/14 15:42:00 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will get the current time in milliseconds.
long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

// This function will initialize the philosophers struct. (t_philo)
// At the end, we initialize the philosophers struct in the arguments struct.
void	init_philos(t_arg *args)
{
	int		i;
	int		total_philos;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * args->philo_num);
	i = 0;
	total_philos = args->philo_num;
	while (i < total_philos)
	{
		philo[i].id = i;
		philo[i].philo_num = args->philo_num;
		philo[i].total_meals_eaten = 0;
		philo[i].total_meals = args->meals_num;
		philo[i].time_to_die = args->time_to_die;
		philo[i].time_to_eat = args->time_to_eat;
		philo[i].time_to_sleep = args->time_to_sleep;
		philo[i].last_meal = ft_time();
		philo[i].limit = args->time_to_die;
		philo[i].stop = 0;
		philo[i].left_fork = &args->forks[philo[i].id];
		philo[i].right_fork = &args->forks[(philo[i].id + 1) % args->philo_num];
		philo[i].args = args;
		i++;
	}
	args->philos = philo;
}
