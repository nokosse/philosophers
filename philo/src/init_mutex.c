/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:54:08 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 17:44:16 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will init the mutexes.
// In the whole program, there are 2 mutexes:
// 1. lock_print: the mutex for printing, so that the output is not mixed.
//	so it prints only one philo status at a time.
// 2. forks: the mutex for the forks, so that the forks are not used by
//	multiple philosophers at the same time.
void	init_mutexes(t_arg *args)
{
	int				nbr_ph;
	pthread_mutex_t	*mutex;

	nbr_ph = args->total_philos;
	mutex = malloc(sizeof(pthread_mutex_t) * nbr_ph);
	while (nbr_ph--)
		pthread_mutex_init(&mutex[nbr_ph], NULL);
	pthread_mutex_init(&args->lock_print, NULL);
	args->forks = mutex;
}

// This function will destroy the mutexes at the end of the program to
// avoid memory leaks.
void	kill_mutexes(t_arg *args)
{
	int	nbr_ph;

	nbr_ph = args->total_philos;
	while (nbr_ph--)
	{
		pthread_mutex_unlock(&args->forks[nbr_ph]);
		pthread_mutex_destroy(&args->forks[nbr_ph]);
	}
	pthread_mutex_unlock(&(*args).lock_print);
	pthread_mutex_destroy(&(*args).lock_print);
}
