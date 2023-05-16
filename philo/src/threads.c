/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:47 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/16 13:08:46 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function is the monitoring thread.
// It is ran by each philo. Meaning if there is 9 philo thread, there will be
// 9 monitoring thread.
// This function is checking if the philo (philo[i]) is dead with check_death.
// If he is dead, it will call dying and dying will write the dying message and
// set the flag to 1, stopping the loop to run, same for the others monitors.
void	*monitoring(void	*data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	while (philo->sarg->flag == 0)
	{
		ft_usleep(1);
		pthread_mutex_lock(&philo->sarg->mtx_time_eat);
		pthread_mutex_lock(&philo->sarg->mtx_finish);
		if (!check_death(philo, 0) && !philo->finish
			&& ((time_now() - philo->last_eat)
				>= (long)(philo->sarg->time2die)))
			dying(philo);
		pthread_mutex_unlock(&philo->sarg->mtx_time_eat);
		pthread_mutex_unlock(&philo->sarg->mtx_finish);
	}
	return (0);
}

// This thread is ran by each philo. 9 philos = this function running 9 times.
// Every odd philo will wait for 10% of the time to eat before starting to eat.
// So every odds philos will have 2 forks, then same for the even philos.
//
// Then, for each philos, we create a thread that will monitor if the philo is
// dead. This thread is created in the 'monitoring' function.
void	*thread(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->sarg->time2eat / 10);
	while (!check_death(philo, 0))
	{
		routine(philo);
		if (++philo->meals_eaten == philo->sarg->meals_to_eat)
		{
			pthread_mutex_lock(&philo->sarg->mtx_finish);
			philo->finish = 1;
			philo->sarg->satiated_philos++;
			if (philo->sarg->satiated_philos == philo->sarg->nb_philo)
			{
				pthread_mutex_unlock(&philo->sarg->mtx_finish);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->sarg->mtx_finish);
			return (0);
		}
	}
	return (0);
}

// This function will be called once, it will launch the threads.
// If in our structure, nb_philo = 9, it will create 
// 9 monitoring thread and 9 philo thread.
int	threading(t_struct *st)
{
	int	i;

	i = 0;
	while (i < st->arg.nb_philo)
	{
		st->philo[i].sarg = &st->arg;
		if (pthread_create(&st->philo[i].thread_death_id, NULL,
				monitoring, &st->philo[i]) != 0)
			return (0);
		if (pthread_create(&st->philo[i].thread_id, NULL,
				thread, &st->philo[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
