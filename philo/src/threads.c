/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:47 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/23 13:05:41 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function is a monitoring thread.
// It is ran only one time in 'threading'.
// This function is checking for each philo if he is dead with check_death.
// If he is dead, it will call dying and dying will write the dying message and
// set the flag to 1, stopping the loop to run.
void	*monitoring(void *data)
{
	t_struct	*st;
	t_philo		*philo;
	int			i;

	st = (t_struct *)data;
	i = 0;
	while (i < st->arg.nb_philo)
	{
		philo = &st->philo[i];
		while (st->arg.flag == 0)
		{
			ft_usleep(10);
			pthread_mutex_lock(&st->arg.mtx_time_eat);
			pthread_mutex_lock(&st->arg.mtx_finish);
			if (!check_death(philo, 0) && !philo->finish
				&& (time_now() - philo->last_eat) >= (long)(st->arg.time2die))
			{
				dying(philo);
			}
			pthread_mutex_unlock(&st->arg.mtx_time_eat);
			pthread_mutex_unlock(&st->arg.mtx_finish);
		}
		i++;
	}
	return (0);
}

// This is the thread that runs for each philos.
// It check if the philo ID is even.
// If it's even, it will usleep the philo to make the even philo
// start eating later than the odd philo.
//
// Then, the while loop will run the messages and will check if
// the philo has done eaten enough, or if the philo is dead.
// It will stop the loop if this is the case thanks to the
// check_death function and the finish flag.
void	*phithread(void *data)
{
	t_philo	*philo;

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
				pthread_mutex_lock(&philo->sarg->mtx_finish);
			}
			pthread_mutex_unlock(&philo->sarg->mtx_finish);
			return (0);
		}
	}
	return (0);
}

// This function will be called once, it will launch the threads.
// If in our structure, nb_philo = 9, it will create 9 threads.
// It will also create only one monitoring thread.
int	threading(t_struct *st)
{
	int			i;
	pthread_t	monithread;

	i = 0;
	while (i < st->arg.nb_philo)
	{
		st->philo[i].sarg = &st->arg;
		if (pthread_create(&st->philo[i].thread_id, NULL,
				phithread, &st->philo[i]) != 0)
			return (0);
		i++;
	}
	pthread_create(&monithread, NULL, monitoring, &st->philo);
	pthread_join(monithread, NULL);
	return (1);
}
