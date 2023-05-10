/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:13:05 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/10 18:51:40 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	write_status(char *str, t_philo *ph)
{
	long int		time;

	time = -1;
	time = actual_time() - ph->pa->start_t;
	if (!check_death(ph, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", ph->id, str);
	}
}

void	sleep_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->mutex_print);
	write_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->pa->mutex_print);
	ft_usleep(ph->pa->sleep);
	pthread_mutex_lock(&ph->pa->mutex_print);
	write_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->pa->mutex_print);
}

void	activity(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork);
	pthread_mutex_lock(&ph->pa->mutex_print);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->mutex_print);
	if (!ph->right_fork)
	{
		ft_usleep(ph->pa->die * 2);
		return ;
	}
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(&ph->pa->mutex_print);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->mutex_print);
	pthread_mutex_lock(&ph->pa->mutex_print);
	write_status("is eating\n", ph);
	pthread_mutex_lock(&ph->pa->time_eat);
	ph->ms_eat = actual_time();
	pthread_mutex_unlock(&ph->pa->time_eat);
	pthread_mutex_unlock(&ph->pa->mutex_print);
	ft_usleep(ph->pa->eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_think(ph);
}
