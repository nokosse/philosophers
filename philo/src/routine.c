/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:50:41 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 19:12:42 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_cnt_of_meals(t_philo *philo)
{
	int	flag_enough;
	int	i;

	if (philo->total_meals_eaten != -1 \
		&& philo->total_meals > 0)
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

void	*ft_process(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->last_meal = ms_now();
	philo->start_time = ms_now();
	while (!philo->arg->is_dead)
	{
		if (philo->arg->is_dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		taking_forks(philo);
		if (philo->arg->is_dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		eating(philo);
		if (philo->arg->is_dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		sleeping(philo);
		if (philo->arg->is_dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		thinking(philo);
		if (philo->arg->is_dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
	}
	return (NULL);
}
