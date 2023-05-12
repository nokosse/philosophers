/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:13:05 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 13:15:24 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(char *str, t_philo *ph)
{
	long int		time;

	time = actual_time() - ph->sarg->start_t;
	if (!check_death(ph, 0))
		printf("%ld %d %s", time, ph->id, str);
}

void	thinking(t_philo *ph)
{
	pthread_mutex_lock(&ph->sarg->mutex_print);
	print_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->sarg->mutex_print);
}

void	sleeping(t_philo *ph)
{
	pthread_mutex_lock(&ph->sarg->mutex_print);
	print_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->sarg->mutex_print);
	ft_usleep(ph->sarg->sleep);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork);
	pthread_mutex_lock(&ph->sarg->mutex_print);
	print_status("has taken arg fork\n", ph);
	pthread_mutex_unlock(&ph->sarg->mutex_print);
	if (!ph->right_fork)
	{
		ft_usleep(ph->sarg->die * 2);
		return ;
	}
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(&ph->sarg->mutex_print);
	print_status("has taken arg fork\n", ph);
	pthread_mutex_unlock(&ph->sarg->mutex_print);
	pthread_mutex_lock(&ph->sarg->mutex_print);
	print_status("is eating\n", ph);
	pthread_mutex_lock(&ph->sarg->time_eat);
	ph->last_eat = actual_time();
	pthread_mutex_unlock(&ph->sarg->time_eat);
	pthread_mutex_unlock(&ph->sarg->mutex_print);
	ft_usleep(ph->sarg->eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
}

void	activity(t_philo *ph)
{
	eating(ph);
	sleeping(ph);
	thinking(ph);
}
