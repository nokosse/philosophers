/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:11 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 16:27:46 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->sarg->dead);
	if (i != 0)
		philo->sarg->flag = i;
	if (philo->sarg->flag)
		return (pthread_mutex_unlock(&philo->sarg->dead), 1);
	pthread_mutex_unlock(&philo->sarg->dead);
	return (0);
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	print_status(char *str, t_philo *philo)
{
	long int		time;

	time = actual_time() - philo->sarg->time_start;
	if (!check_death(philo, 0))
		printf("%ld %d %s", time, philo->id, str);
}
