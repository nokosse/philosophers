/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:46:53 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/02 17:12:04 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// We unlock the forks in routine_eat.c when the philo is done eating.
void	forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ld %d has taken a fork\n", \
			ms_now() - philo->start_time, philo->id + 1);
		printf("%ld %d has taken a fork\n", \
			ms_now() - philo->start_time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

void	forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ld %d has taken a fork\n", \
			ms_now() - philo->start_time, philo->id + 1);
		printf("%ld %d has taken a fork\n", \
			ms_now() - philo->start_time, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

// The philosophers with EVEN id take the RIGHT fork THEN the LEFT fork.
// The philosophers with ODD  id take the LEFT fork THEN the RIGHT fork.
// This is how we avoid deadlocks.
//
// Only the EVEN philos will take the fork, while the ODDS wait.
// (The last philo is counted as EVEN)
// When they eat, there will be 0 forks avaliable.
// Then the ODD philos will take the fork, while the EVENS wait.
// When they eat, there will be 0 forks avaliable.
// etc...
//
// But where do they 'wait'? I dont have any functions or usleep for that.
// It's implicitly manged by 'pthread_mutex_lock'. It locks the thread while
// the mutex is locked by another thread, creating a queue.
void	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->id + 1 != philo->total_philos)
		forks_even(philo);
	else
		forks_odd(philo);
}
