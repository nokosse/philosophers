/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:54:08 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/03 14:34:29 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Why we need to write our own usleep function?
// Because the usleep function is not precise enough.
// The original usleep will sleep for at least the time specified in its
// argument. But the time specified may be rounded up to the nearest or 
// truncated to the nearest system clock tick. Meaning that the real time
// slept may be longer or shorter than the time specified, and that's why
// usleep is not precise enough.
//
// So we write our own usleep that is more precise. How ?
// It measures the actual time in milliseconds, then uses a whie loop to
// sleep for the time specified in the argument. But this may be more
// ressource consuming than the original usleep.
// To make it quick, it's more precise because we use the 'ms_now' function
// and we do some maths with milliseconds.
void	ft_usleep(int ms)
{
	long	time;

	time = ms_now();
	usleep(ms * 920);
	while (ms_now() < time + ms)
		usleep(ms * 3);
}

// ms_now is a very useful function in all the program.
// This function will return the actual time in milliseconds. (since the Epoch)
// Right now it is around 53 years and 4 months since the Epoch. (03/05/2023)
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
	struct timeval	timeval;
	long			res;

	gettimeofday(&timeval, NULL);
	res = 1000 * (size_t)timeval.tv_sec + (size_t)timeval.tv_usec / 1000;
	return (res);
}
