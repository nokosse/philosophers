/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 15:29:06 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// We have to create our own usleep function because the usleep function
// is not precise enough. We will use the gettimeofday function to get the
// current time in milliseconds, and we will compare it to the start time
// to know how much time has passed.
void	ft_usleep(int ms)
{
	long	time;

	time = time_ms();
	usleep(ms * 1000);
	while (time_ms() - time < ms)
		usleep(ms * 3);
}

// This function will return the current time in milliseconds.
long	time_ms(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

// This function will just print the error message.
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
	init_mutexes(&args);
	init_philos(&args);
	init_threads(&args);
	kill_threads(&args);
	kill_mutexes(&args);
	return (1);
}
