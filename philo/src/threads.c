/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:47 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 13:17:36 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->sarg->die + 1);
	pthread_mutex_lock(&ph->sarg->time_eat);
	pthread_mutex_lock(&ph->sarg->finish);
	if (!check_death(ph, 0) && !ph->finish
		&& ((actual_time() - ph->last_eat) >= (long)(ph->sarg->die)))
	{
		pthread_mutex_unlock(&ph->sarg->time_eat);
		pthread_mutex_unlock(&ph->sarg->finish);
		pthread_mutex_lock(&ph->sarg->mutex_print);
		print_status("died\n", ph);
		pthread_mutex_unlock(&ph->sarg->mutex_print);
		check_death(ph, 1);
	}
	pthread_mutex_unlock(&ph->sarg->time_eat);
	pthread_mutex_unlock(&ph->sarg->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->sarg->eat / 10);
	while (!check_death(ph, 0))
	{
		pthread_create(&ph->thread_death_id, NULL, is_dead, data);
		activity(ph);
		pthread_detach(ph->thread_death_id);
		if ((int)++ph->nb_eat == ph->sarg->meals_to_eat)
		{
			pthread_mutex_lock(&ph->sarg->finish);
			ph->finish = 1;
			ph->sarg->satiated_philos++;
			if (ph->sarg->satiated_philos == ph->sarg->total)
			{
				pthread_mutex_unlock(&ph->sarg->finish);
				check_death(ph, 2);
			}
			pthread_mutex_unlock(&ph->sarg->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	threading(t_struct *p)
{
	int	i;

	i = 0;
	while (i < p->arg.total)
	{
		p->ph[i].sarg = &p->arg;
		if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
