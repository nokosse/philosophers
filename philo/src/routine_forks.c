/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:46:53 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 19:12:34 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	taking_left_then_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ldms philo[%d] 🍴🍴 has taken a fork\n", \
			ms_now() - philo->start_time, philo->id + 1);
		printf("%ldms philo[%d] 🍴🍴 has taken a fork\n", \
			ms_now() - philo->start_time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

void	taking_right_then_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ldms philo[%d] 🍴🍴 has taken a fork\n", \
			ms_now() - philo->start_time, philo->id + 1);
		printf("%ldms philo[%d] 🍴🍴 has taken a fork\n", \
			ms_now() - philo->start_time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

// Philo will take right fork first when id is even and not last
// Philo will take left fork first when id is odd or last
void	taking_forks(t_philo *philo)
{
	if ((philo->id) % 2 == 0 && philo->id + 1 != philo->total_philos)
		taking_right_then_left_fork(philo);
	else
		taking_left_then_right_fork(philo);
}
