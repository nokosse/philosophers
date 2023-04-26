/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:53:23 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/26 18:17:00 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will init the threads.
// In the whole program, there are 2 (types of) threads:
// 1. the monitoring thread, which is 's_tid'.
//		It will continuously check if the philos are alive.
// 2. the philo threads, which are 'threads'.
//		They will execute the philo_routine function. (eat, sleep...)
void	init_threads(t_arg *args)
{
	int			nbr_ph;
	pthread_t	*threads;
	pthread_t	s_tid;

	nbr_ph = args->total_philos;
	threads = malloc(sizeof(pthread_t) * nbr_ph);
	while (nbr_ph)
	{
		nbr_ph--;
		pthread_create(&threads[nbr_ph], NULL, philo_routine,
			(void *)&args->philos[nbr_ph]);
	}
	pthread_create(&s_tid, NULL, monitoring, (void *)args->philos);
	pthread_join(s_tid, NULL);
	args->threads_id = threads;
}

// This function will destroy the threads at the end of the program to
// avoid memory leaks.
void	kill_threads(t_arg *args)
{
	int	nbr_ph;

	nbr_ph = args->total_philos;
	if (nbr_ph == 1)
	{
		pthread_mutex_unlock(&args->forks[0]);
	}
	while (nbr_ph)
	{
		nbr_ph--;
		pthread_join(args->threads_id[nbr_ph], NULL);
	}
}
