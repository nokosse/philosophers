/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:47:52 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/14 16:47:38 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will initialize the threads.
// First, in the loop, we create a thread for each philosopher.
// Then, we create a thread for the check_death function.
// At the end, we join the thread_ids.
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
	}
	pthread_create(&thread_ids, NULL, check_death, (void *)args->philo_num);
	pthread_join(thread_ids, NULL);
	args->thread_ids = threads;
}
