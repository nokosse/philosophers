/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:12:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 14:36:42 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_right_then_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->print_lock);
	if (philo->stop != 1)
	{
		printf("%ldms philo[%d] has taken a fork 🍴\n",
			time_ms() - philo->start, philo->id + 1);
		printf("%ldms philo[%d] has taken a fork 🍴\n",
			time_ms() - philo->start, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->print_lock);
}

void	take_left_then_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->print_lock);
	if (philo->stop != 1)
	{
		printf("%ldms philo[%d] has taken a fork 🍴\n",
			time_ms() - philo->start, philo->id + 1);
		printf("%ldms philo[%d] has taken a fork 🍴\n",
			time_ms() - philo->start, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->print_lock);
}

void	take_forks(t_philo *philo)
{
	if ((philo->id) % 2 == 0 && philo->id + 1 != philo->philo_num)
		take_right_then_left_fork(philo);
	else
		take_left_then_right_fork(philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_lock);
	printf("%ldms philo[%d] is eating 🍝\n",
		time_ms() - philo->start, philo->id + 1);
	pthread_mutex_unlock(&philo->print_lock);
	philo->total_meals_eaten += 1;
	philo->last_meal = time_ms();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}