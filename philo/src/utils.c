/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:11 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/16 13:08:46 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// In this function we have a mutex : 'dead'
// It protects the 'flag' variable from being changed by multiple
// threads at the same time.
int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->sarg->mtx_dead);
	if (i != 0)
		philo->sarg->flag = i;
	if (philo->sarg->flag)
		return (pthread_mutex_unlock(&philo->sarg->mtx_dead), 1);
	pthread_mutex_unlock(&philo->sarg->mtx_dead);
	return (0);
}

// This functioon will return the current time in milliseconds.
// EXPLANATION:
// gettimeofday() returns the actual time in microseconds. (since 1970)
// the timeval structure has two members: tv_sec and tv_usec.
// tv_sec is the number of seconds since 1970.
// tv_usec is the number of microseconds since the last second.
// What we do here is :
// We multiply the number of seconds by 1000 to convert it to milliseconds.
// We divide the number of microseconds by 1000 to convert it to milliseconds.
// We add the two numbers to get the current time in milliseconds.
// And then we have our current time in milliseconds.
long int	time_now(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	print_status(char *str, t_philo *philo)
{
	long int		time;

	time = time_now() - philo->sarg->time_start;
	if (!check_death(philo, 0))
		printf("%ld %d %s", time, philo->id, str);
}
