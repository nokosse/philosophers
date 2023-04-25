/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:59:10 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 15:10:14 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_died(t_philo *philo, int i)
{
	philo->args->is_dead = 1;
	pthread_mutex_lock(&philo->print_lock);
	printf("%ldms philo %d died !\n", time_ms() - philo->start, philo[i].id + 1);
	i = -1;
	while (i < philo[i].philo_num)
	{
		philo[i].stop = 1;
		i++;
	}
}

void	*check_death(void *args)
{
	t_philo 	*philo;
	long int	time;
	int			i;

	philo = (t_philo *)args;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = 0;
		while (i < philo->philo_num)
		{
			time = time_ms();
			if (time - philo[i].last_meal > philo[i].limit)
			{
				philo_died(philo, i);
				pthread_mutex_unlock(&philo->print_lock);
				return (NULL);
			}
		}
		if (meals_count(philo) || philo->stop == 1)
			return (NULL);
	}
	return (NULL);
}