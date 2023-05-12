/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:13:05 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 15:59:13 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	dying(t_philo *philo)
{
	pthread_mutex_unlock(&philo->sarg->time_eat);
	pthread_mutex_unlock(&philo->sarg->finish);
	pthread_mutex_lock(&philo->sarg->mutex_print);
	print_status("died 💀💀 👎😹👎 😂🤣\n", philo);
	pthread_mutex_unlock(&philo->sarg->mutex_print);
	check_death(philo, 1);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->sarg->mutex_print);
	print_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->sarg->mutex_print);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->sarg->mutex_print);
	print_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->sarg->mutex_print);
	ft_usleep(philo->sarg->time2sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->sarg->mutex_print);
	print_status("has taken arg fork\n", philo);
	pthread_mutex_unlock(&philo->sarg->mutex_print);
	if (!philo->right_fork)
	{
		ft_usleep(philo->sarg->time2die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->sarg->mutex_print);
	print_status("has taken arg fork\n", philo);
	pthread_mutex_unlock(&philo->sarg->mutex_print);
	pthread_mutex_lock(&philo->sarg->mutex_print);
	print_status("is eating\n", philo);
	pthread_mutex_lock(&philo->sarg->time_eat);
	philo->last_eat = actual_time();
	pthread_mutex_unlock(&philo->sarg->time_eat);
	pthread_mutex_unlock(&philo->sarg->mutex_print);
	ft_usleep(philo->sarg->time2eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	routine(t_philo *philo)
{
	eating(philo);
	sleeping(philo);
	thinking(philo);
}
