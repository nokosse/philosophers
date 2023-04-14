/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:08:31 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/14 15:44:07 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will initialize the arguments.
// It will put our agruments in the struct t_arg.
//
// Will return 0 if argument 1 or 5 is less than 1.
// (number of philosophers or number of meals)
int	init_args(t_arg *args, int ac, char **av)
{
	args->is_dead = 0;
	args->philo_num = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->meals_num = ft_atoi(av[5]);
	if (ac == 5)
	{
		if (args->philo_num < 1)
			return (0);
		args->meals_num = -1;
	}
	if (ac == 6)
	{
		if (args->meals_num < 1)
			return (0);
	}
	return (1);
}
