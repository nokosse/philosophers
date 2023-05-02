/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:53:23 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/02 16:59:47 by kvisouth         ###   ########.fr       */
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
	int			nbphilos;
	pthread_t	*threads;
	pthread_t	s_tid;

	nbphilos = args->total_philos;
	threads = malloc(sizeof(pthread_t) * nbphilos);
	while (nbphilos > 0)
	{
		nbphilos--;
		pthread_create(&threads[nbphilos], NULL, philo_routine,
			(void *)&args->philos[nbphilos]);
	}
	pthread_create(&s_tid, NULL, dead_checker, (void *)args->philos);
	pthread_join(s_tid, NULL);
	args->threads_id = threads;
}

// This function will destroy the threads at the end of the program to
// avoid memory leaks.
void	kill_threads(t_arg *args)
{
	int	nbphilos;

	nbphilos = args->total_philos;
	if (nbphilos == 1)
	{
		pthread_mutex_unlock(&args->forks[0]);
	}
	while (nbphilos)
	{
		nbphilos--;
		pthread_join(args->threads_id[nbphilos], NULL);
	}
}
