/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 17:28:29 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Why not ?
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

void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	free_all(t_arg *args)
{
	free(args->threads_id);
	free(args->philos);
	free(args->forks);
}

// The goal of philosopher is to understand the basics of threads and mutexes.
// A philosopher is a thread. And the forks they eat with are mutexes.
// Every threads must have 2 mutexes to eat.
// But Every threads have only 1 mutex. So they must share it.
//
// arg1 = number_of_philosophers
// arg2 = time_to_die (ms)
// arg3 = time_to_eat (ms)
// arg4 = time_to_sleep (ms)
// arg5 = number_of_times_each_philosopher_must_eat
//
// When the philosopher eats, it resets its timer. (time_to_die)

int	main(int ac, char **av)
{
	t_arg	args;

	if (!valid_args_check(ac, av) || !check_int_max(av))
		return (invalid_args_msg(), 0);
	if (init_args(&args, ac, av) == 1)
		return (0);
	init_mutexes(&args);
	init_philos(&args);
	init_threads(&args);
	kill_threads(&args);
	kill_mutexes(&args);
	free_all(&args);
	return (1);
}
