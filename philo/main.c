/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 19:11:57 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms)
{
	long	time;

	time = ms_now();
	usleep(ms * 920);
	while (ms_now() < time + ms)
		usleep(ms * 3);
}

// ms_now is a very useful function in all the program.
// This function will return the actual time in milliseconds.
//
// We initialize a timeval structure. It's a structure that contains 2 members:
// tv_sec and tv_usec.
// tv_sec : stores the number of seconds since the Epoch.
// tv_usec : stores the number of microseconds since the last second.
//
// the gettimeofday() function fills the structure with the actual time.
// The first argument &tv is the address of the structure. (timeval)
// The second argument is the timezone. We don't need it so we put NULL.
//
// We then calculate the elapsed time between the Epoch and the actual time
// in milliseconds, and stores the result in 'res'.
// It multiplies the seconds by 1000 to convert them to milliseconds.
// And it divides the microseconds by 1000 to get the decimal part of the
// milliseconds.
//
// Then it returns the result.
long	ms_now(void)
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
