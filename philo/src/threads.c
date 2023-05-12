/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:47 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 17:49:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This monitoring thread will check if the philo is dead
// The 'mtx_time_eat' mutex is used to protect the 'last_eat' variable, like the
// 'dead' mutex in the utils.c file. This is the purpose of the mutex.
//
// It will check if the philo is dead with the 'check_death' function, and if
// he is not dead, it will check if he is satiated (philo->finish), and if he
// is not satiated, it will check if he is starving (time since last meal >=
// time to die). If he is starving, he will die. (we call the 'dying' function)
//
// To resume, a philo die when : he is not satiated and he is starving.
void	*monitoring(void	*data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->sarg->time2die + 1);
	pthread_mutex_lock(&philo->sarg->mtx_time_eat);
	pthread_mutex_lock(&philo->sarg->mtx_finish);
	if (!check_death(philo, 0) && !philo->finish
		&& ((actual_time() - philo->last_eat) >= (long)(philo->sarg->time2die)))
		dying(philo);
	pthread_mutex_unlock(&philo->sarg->mtx_time_eat);
	pthread_mutex_unlock(&philo->sarg->mtx_finish);
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
		pthread_create(&philo->thread_death_id, NULL, monitoring, data);
		routine(philo);
		pthread_detach(philo->thread_death_id);
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
