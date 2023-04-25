/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:47:58 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 18:07:17 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function prints that the philosopher is eating.
// It also updates the total meals eaten by the philosopher.
// It also updates the last meal time of the philosopher.
//
// We lock the mutexes to print.
void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ldms philo[%d] 🍝😋 is eating\n", \
		ft_time() - philo->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	philo->total_meals += 1;
	philo->last_meal = ft_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
