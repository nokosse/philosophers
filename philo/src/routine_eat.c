/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:47:58 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/28 14:59:04 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function prints that the philosopher is eating.
//
// We increment the total meals of the philosopher by 1.
// Then we refresh the last meal time of the philosopher to now.
// Then we sleep for the time to eat.
// Finally we unlock the forks. (they were locked in taking_forks() function)
void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is eating\n", \
		ms_now() - philo->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	philo->total_meals_eaten += 1;
	philo->last_meal = ms_now();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
