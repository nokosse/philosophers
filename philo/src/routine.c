/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:50:41 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/03 15:01:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function is used to count the number of meals eaten by the philosophers.
// It's used to check if the philos have eaten the required number of times.
// We check if total_meals > 0, to check if the optional argument is present.
// If there is no optional argument, we directly return 0.
int	count_meals(t_philo *philo)
{
	int	flag_enough;
	int	i;

	if (philo->total_meals_eaten != -1 && philo->total_meals > 0)
	{
		flag_enough = 1;
		i = -1;
		while (++i < philo->total_philos)
			if (philo[i].total_meals_eaten < philo->total_meals)
				flag_enough = 0;
		if (flag_enough == 1)
		{
			i = -1;
			while (i < philo[i].total_philos)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

// This function is the thread of every philosopher.
// In the loop, it always checks if :
// - the philosopher is dead
// - the flag 'stop' is set to 1
// - the philosopher has eaten enough (optionnal argument)
// If one of these conditions is true, the function returns NULL.
// Else, it continues.
void	*philo_routine(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->last_meal = ms_now();
	philo->start_time = ms_now();
	while (philo->arg->is_dead == 0)
	{
		if (philo->arg->is_dead || philo->stop || count_meals(philo))
			return (NULL);
		taking_forks(philo);
		if (philo->arg->is_dead || philo->stop || count_meals(philo))
			return (NULL);
		eating(philo);
		if (philo->arg->is_dead || philo->stop || count_meals(philo))
			return (NULL);
		sleeping(philo);
		if (philo->arg->is_dead || philo->stop || count_meals(philo))
			return (NULL);
		thinking(philo);
		if (philo->arg->is_dead || philo->stop || count_meals(philo))
			return (NULL);
	}
	return (NULL);
}

// This function is used to 'keep an eye' on the philosophers.
// It checks the state of every philosophers to check if they are dying.
//
// The loop checks one by one philosopher's last meal time.
// It then compares the elapsed time between 'last_meal' and 'limit_death'.
// last_meal is the time when the philosopher last ate.
// limit_death is (max) time that the philosopher can live without eating.
// If the elapsed time is greater than limit_death, we call the function that
// kills the philosopher (kill_philo).
//
// For the optional argument, which is optional, we just check if all the
// philosophers have eaten the required number of times.
// If so, we return NULL, which will stop the thread.
//
// It's executed by a thread, this is the second type of thread in question.
// It's called a monitoring thread.
void	*dead_checker(void *args)
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
				kill_philo(philo, i);
				pthread_mutex_unlock(&philo->lock_print);
				return (NULL);
			}
		}
		if (count_meals(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}
