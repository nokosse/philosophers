/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:53:03 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/26 16:02:52 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will init the 't_philo' structure with the arguments.
// Special mention to forks ;
// philos[i].right_fork = &args->forks[(philos[i].id + 1) % args->total_philos];
// This line means that the right fork of the philosopher is the fork at the
// right of the philosopher.
void	init_philos(t_arg *args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->total_philos);
	while (i < args->total_philos)
	{
		philos[i].id = i;
		philos[i].total_philos = args->total_philos;
		philos[i].total_meals_eaten = 0;
		philos[i].total_meals = args->nbr_of_meals;
		philos[i].time_to_eat = args->time_to_eat;
		philos[i].time_to_sleep = args->time_to_sleep;
		philos[i].time_to_die = args->time_to_die;
		philos[i].last_meal = ms_now();
		philos[i].limit_death = args->time_to_die;
		philos[i].stop = 0;
		philos[i].left_fork = &args->forks[philos[i].id];
		philos[i].right_fork = &args->forks[(philos[i].id + 1)
			% args->total_philos];
		philos[i].arg = args;
		i++;
	}
	args->philos = philos;
}

// This function will init the 't_arg' structure with the arguments.
int	init_args(t_arg *args, int argc, char **argv)
{
	args->total_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->is_dead = 0;
	if (argc == 6)
		args->nbr_of_meals = ft_atoi(argv[5]);
	if (argc == 5)
	{
		if (args->total_philos < 1)
			return (0);
		args->nbr_of_meals = -1;
	}
	if (argc == 6)
	{
		if (args->nbr_of_meals < 1)
			return (0);
	}
	return (0);
}
