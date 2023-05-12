/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:47 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 15:58:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This monitoring thread will check if the philo is dead
void	*monitoring(void	*data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->sarg->time2die + 1);
	pthread_mutex_lock(&philo->sarg->time_eat);
	pthread_mutex_lock(&philo->sarg->finish);
	if (!check_death(philo, 0) && !philo->finish
		&& ((actual_time() - philo->last_eat) >= (long)(philo->sarg->time2die)))
		dying(philo);
	pthread_mutex_unlock(&philo->sarg->time_eat);
	pthread_mutex_unlock(&philo->sarg->finish);
	return (0);
}

void	*thread(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->sarg->time2eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death_id, NULL, monitoring, data);
		routine(philo);
		pthread_detach(philo->thread_death_id);
		if ((int)++philo->nb_eat == philo->sarg->meals_to_eat)
		{
			pthread_mutex_lock(&philo->sarg->finish);
			philo->finish = 1;
			philo->sarg->satiated_philos++;
			if (philo->sarg->satiated_philos == philo->sarg->nb_philo)
			{
				pthread_mutex_unlock(&philo->sarg->finish);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->sarg->finish);
			return (0);
		}
	}
	return (0);
}

int	threading(t_struct *st)
{
	int	i;

	i = 0;
	while (i < st->arg.nb_philo)
	{
		st->philo[i].sarg = &st->arg;
		if (pthread_create(&st->philo[i].thread_id, NULL,
				thread, &st->philo[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
