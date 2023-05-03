/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:47:17 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/03 17:07:55 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is eating\n", ph);
	pthread_mutex_lock(&ph->pa->time_eat);
	ph->ms_eat = actual_time();
	pthread_mutex_unlock(&ph->pa->time_eat);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->eat);
	pthread_mutex_unlock(ph->r_f);
	pthread_mutex_unlock(&ph->l_f);
}

void	taking_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	if (!ph->r_f)
	{
		ft_usleep(ph->pa->die * 2);
		return ;
	}
	pthread_mutex_lock(ph->r_f);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}

void	sleeping(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->sleep);
}

void	thinking(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}

void	activity(t_philo *ph)
{
	taking_forks(ph);
	eating(ph);
	sleeping(ph);
	thinking(ph);
}
