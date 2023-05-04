/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:48:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/04 14:44:14 by kvisouth         ###   ########.fr       */
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

int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->pa->dead);
	if (i)
		ph->pa->stop = i;
	if (ph->pa->stop)
	{
		pthread_mutex_unlock(&ph->pa->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->pa->dead);
	return (0);
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
