/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:53:23 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 17:55:47 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will init the threads.
// In the whole program, there are 2 threads:
// 1. threads: the thread for each philosopher.
//	If there is 4 philosophers, there will be 4 threads..
// 2. s_tid: the thread for the monitor.
//	The monitor thread will check the status of the philosophers.
void	init_threads(t_arg *args)
{
	int			nbr_ph;
	pthread_t	*threads;
	pthread_t	s_tid;

	nbr_ph = args->total_philos;
	threads = malloc(sizeof(pthread_t) * nbr_ph);
	while (nbr_ph--)
		pthread_create(&threads[nbr_ph], \
			NULL, ft_process, (void *)&args->philos[nbr_ph]);
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
