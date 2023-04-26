/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:50:41 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/26 18:58:26 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
void	*philo_routine(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->last_meal = ms_now();
	philo->start_time = ms_now();
	while (!philo->arg->is_dead)
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
// The loop checks the philosopher's last meal time one by one.
// It then compares the elapsed time between 'last_meal' and 'limit_death'.
// last_meal is the time when the philosopher last ate.
// limit_death is (max) time that the philosopher can live without eating.
// If the elapsed time is greater than limit_death, the philosopher dies.
// We then call the dying function. (see above)
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
x
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
				dying(philo, i);
				return (NULL);
			}
		}
		if (count_meals(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}
