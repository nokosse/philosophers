/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:51:14 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/28 14:55:52 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function is called whenever a philosopher dies.
// It sets the is_dead flag to 1, which is checked in the monitor thread.
// We lock the lock_print then print the message of death.
// Then, in the loop, we set the stop flag to 1 for all philosophers.
void	kill_philo(t_philo *philo, int i)
{
	philo->arg->is_dead = 1;
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d died\n", ms_now() - philo->start_time,
		philo[i].id + 1);
	i = -1;
	while (i < philo[i].total_philos)
	{
		philo[i].stop = 1;
		i++;
	}
	pthread_mutex_unlock(&philo->lock_print);
}
