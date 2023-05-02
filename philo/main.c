/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/02 16:15:23 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// The routine part of the philosophers will be executed in 'init_threads'.
// REMINDER :
// arg1: number of philosophers
// arg2: time to die
// arg3: time to eat
// arg4: time to sleep
// arg5: number of times each philosopher must eat
int	main(int ac, char **av)
{
	t_arg	args;

	if (!valid_args_check(ac, av) || !check_int_max(av))
		return (invalid_args_msg(), 0);
	init_args(&args, ac, av);
	init_mutexes(&args);
	init_philos(&args);
	init_threads(&args);
	kill_threads(&args);
	kill_mutexes(&args);
	free_args(&args);
	return (1);
}

// So, how do this program works to avoid the philosopher dying?
//
// First, we need to understand the routine of the philosopher.
// A philosopher must : eat, sleep, think, eat ...
// 
// ### HOW DO THEY EAT? ###
// Each philosophers has only one fork, but he needs two to eat.
// So when a philosopher wants to eat, he will have to borrow the fork
// of his neighbor.
// If all the philosophers takes their forks at the same time, there will
// be a deadlock.
// So what we do is : 'EVEN' philosophers will take their left fork first,
// then borrow the right fork and eat.
// Once they are done eating, they will put down their forks. (unlock)
// And the 'ODD' philosophers will borrow the right fork first, then the
// left fork and eat.
//
// So if you imagine a round table with philos around, 1 out of 2 will eat
// simultaneously.
//
// And how does it works ?
// I explain this in the file 'routine_forks.c'.