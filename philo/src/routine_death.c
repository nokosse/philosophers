/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:51:14 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 19:12:27 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function is called whenever a philosopher dies.
// It sets the is_dead flag to 1, which is checked in the monitor thread.
// We lock the lock_print then print the message of death.
// Then, in the loop, we set the stop flag to 1 for all philosophers.
void	died_philo(t_philo *philo, int i)
{
	philo->arg->is_dead = 1;
	pthread_mutex_lock(&philo->lock_print);
	printf("%ldms philo[%d] died 💀💀\n", ms_now() - philo->start_time,
		philo[i].id + 1);
	i = -1;
	while (i < philo[i].total_philos)
	{
		philo[i].stop = 1;
		i++;
	}
}

// This function is used to 'keep an eye' on the philosophers.
// It checks the state of every philosophers to check if they are dying.
//
// The loop checks the philosopher's last meal time one by one.
// It then compares the elapsed time between 'last_meal' and 'limit_death'.
// last_meal is the time when the philosopher last ate.
// limit_death is (max) time that the philosopher can live without eating.
// If the elapsed time is greater than limit_death, the philosopher dies.
// We then call the died_philo function. (see above)
//
// For the optional argument, which is optional, we just check if all the
// philosophers have eaten the required number of times.
// If so, we return NULL, which will stop the thread.
//
// It's executed by a thread, this is the second type of thread in question.
// It's called a monitoring thread.
void	*monitoring(void *args)
{
	t_philo	*philo;
	long	time_now;
	int		i;

	philo = (t_philo *)args;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = -1;
		while (++i < philo->total_philos)
		{
			time_now = ms_now();
			if (time_now - philo[i].last_meal > philo[i].limit_death)
			{
				died_philo(philo, i);
				pthread_mutex_unlock(&philo->lock_print);
				return (NULL);
			}
		}
		if (ft_cnt_of_meals(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}
