/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/14 14:29:15 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Just the error message displayed when the arguments are invalid.
void	invalid_args_msg(void)
{
	printf("Error	: Invalid arguments\n\n");
	printf("Usage	: ./philo arg1 arg2 arg3 arg4 (arg5)\n");
	printf("arg1 	: 🚹number_of_philosophers\n");
	printf("arg2	: 💀time_to_die (ms)\n");
	printf("arg3	: 🍝time_to_eat (ms)\n");
	printf("arg4	: 💤time_to_sleep (ms)\n");
	printf("(arg5)	: number_of_times_each_philosopher_must_eat\n\n");
	printf("Example	: ./philo 5 800 200 200\n");
	printf("Example	: ./philo 5 800 200 200 7\n");
}

// 1. We check the arguments.
// 2. We initialize the arguments to use them later. (t_arg args)
// 3. We initialize the mutexes. (forks, print, death)
// 4. We initialize the threads. (philosophers)
int	main(int ac, char **av)
{
	t_arg	args;

	if (!valid_args_check(ac, av) || !check_int_max(av))
		return (invalid_args_msg(), 0);
	if (!init_args(&args, ac, av))
		return (printf("Error	: arguments 1 or 5 must be at least 1.\n"), 0);
	// init_mutexes(&args);
	// init_philos(&args);
	// init_threads(&args);
	return (1);
}
