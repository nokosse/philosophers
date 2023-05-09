/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:48:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/09 13:17:36 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will write "500 1 is eating\n" to stdout.
// 500 is an example of the time in milliseconds since the start of the program.
// 1 is the id of the philosopher.
void	write_status(char *str, t_philo *ph)
{
	long int		time;

	time = -1;
	time = actual_time() - ph->pa->start_t;
	if (check_death(ph, 0) == 0)
		printf("%ld %d %s", time, ph->id, str);
}

// This function will check if the philosopher is dead.
// 'i' is a number (0 or 1 or 2) that we will send from the program.
// If we send 1 or 2 : it will enter the first condition, it will set 'stop'
// to 1 or 2. Then it will return 0.
// If we send 0 : it will enter the second condition (if stop is not 0)
// and it will return 1.
int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->pa->dead);
	if (i != 0)
		ph->pa->stop = i;
	if (ph->pa->stop != 0)
	{
		pthread_mutex_unlock(&ph->pa->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->pa->dead);
	return (0);
}

// This functon returns the current time in milliseconds.
// The timaval structure has 2 members: tv_sec and tv_usec.
// tv_sec is the number of seconds since the Epoch.
// tv_usec is the number of microseconds since the Epoch.
// What we do here is we multiply the number of seconds by 1000 to convert it
// to milliseconds. Then we add the number of microseconds divided by 1000 to
// convert it to milliseconds.
// So we get the number of milliseconds since the Epoch.
long int	actual_time(void)
{
	long int			time;
	struct timeval		timeval;

	time = 0;
	if (gettimeofday(&timeval, NULL) == -1)
		return (0);
	time = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	return (time);
}

// We create our own usleep because the original usleep is not precise enough.
// The original usleep function sleeps the program for milliseconds but it can
// be longer or shorter than the time we want (depending on the OS).
// The ft_usleep is safer because it uses the actual_time function to check
// if the time we want has passed. So it can't be shorter and longer than the
// time we want.
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
