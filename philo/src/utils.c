/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:11 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/31 15:44:12 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
/*
If parameter i = 2, it means the flag will be set to 2.
2 is when all the philos have eaten enough meals.
If parameter i = 1, it means the flag will be set to 1.
1 is when a philo is dead.
And 0 is none of the above, so the simulation continues.
*/
int	check_death(t_philo *philo, int i)
{
	int	flag_value;

	pthread_mutex_lock(&philo->sarg->mtx_flag);
	if (i != 0)
		philo->sarg->flag = i;
	flag_value = philo->sarg->flag;
	pthread_mutex_unlock(&philo->sarg->mtx_flag);
	if (flag_value != 0)
		return (1);
	return (0);
}

/*
This function will return 1 if a philo has a flag different frmo 0.
*/
int	check_death_iter(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->sarg->nb_philo)
	{
		pthread_mutex_lock(&philo->sarg->mtx_flag);
		if (philo->sarg->flag != 0)
		{
			pthread_mutex_unlock(&philo->sarg->mtx_flag);
			return (1);
		}
		pthread_mutex_unlock(&philo->sarg->mtx_flag);
		i++;
	}
	return (0);
}
/*
This functioon will return the current time in milliseconds.
EXPLANATION:
gettimeofday() returns the actual time in microseconds. (since 1970)
the timeval structure has two members: tv_sec and tv_usec.
tv_sec is the number of seconds since 1970.
tv_usec is the number of microseconds since the last second.
What we do here is :
We multiply the number of seconds by 1000 to convert it to milliseconds.
We divide the number of microseconds by 1000 to convert it to milliseconds.
We add the two numbers to get the current time in milliseconds.
And then we have our current time in milliseconds.
*/
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
	{
		pthread_mutex_lock(&philo->sarg->mtx_print_status);
		printf("%ld %d %s", time, philo->id, str);
		pthread_mutex_unlock(&philo->sarg->mtx_print_status);
	}
}
