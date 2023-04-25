/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:42:16 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 15:35:29 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will check if all the philosophers ate enough.
int	meals_count(t_philo *philo)
{
	int	i;
	int	ate_enough;

	if (philo->total_meals != -1 && philo-> total_meals_eaten > 0)
	{
		ate_enough = 1;
		i = 0;
		while (i < philo->philo_num)
		{
			if (philo[i].total_meals < philo->total_meals_eaten)
				ate_enough = 0;
			i++;
		}
		if (ate_enough == 1)
		{
			i = -1;
			while (i < philo[i].philo_num)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->last_meal = time_ms();
	philo->start = time_ms();
	while (philo->args->is_dead != 1)
	{
		if (philo->args->is_dead || philo->stop || meals_count(philo))
			return (NULL);
		printf("TEST SIGSEGV\n");
		take_forks(philo);
		if (philo->args->is_dead || philo->stop || meals_count(philo))
			return (NULL);
		eat(philo);
		if (philo->args->is_dead || philo->stop || meals_count(philo))
			return (NULL);
		sleeping(philo);
		if (philo->args->is_dead || philo->stop || meals_count(philo))
			return (NULL);
		think(philo);
		if (philo->args->is_dead || philo->stop || meals_count(philo))
			return (NULL);
	}
	return (NULL);
}
