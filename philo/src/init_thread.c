/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:47:52 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/14 17:26:33 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will initialize the threads.
// There will be 2 'type' of threads :
// - Philosophers threads, which will be the philosophers themselves.
// - Death thread, which will check if a philosopher is dead.
//
// Because the reason for a thread to exist, is to execute a function.
// One thread will use 'routine', and the other will use 'check_death'.
void	init_threads(t_arg *args)
{
	int			total_philos;
	pthread_t	*threads;
	pthread_t	thread_ids;

	total_philos = args->philo_num;
	threads = malloc(sizeof(pthread_t) * total_philos);
	while (total_philos > 0)
	{
		pthread_create(&threads[total_philos], NULL, routine,
			(void *)&args->philo_num[total_philos]);
		total_philos--;
	}
	pthread_create(&thread_ids, NULL, check_death, (void *)args->philo_num);
	pthread_join(thread_ids, NULL);
	args->thread_ids = threads;
}
