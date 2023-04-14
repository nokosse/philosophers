/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:35:07 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/14 15:03:09 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function will initialize the mutexes.
// In the subject, it is said the there is as many forks as philosophers.
// So we will create as many mutexes as philosophers.
//
// Then we init a "print_lock" mutex. This will be the mutex that will be used
// to print the status of the philosophers. (lock, print, unlock)
//
// Finally, we will store the forks (mutexes) in the args struct
// in the 'forks' variable.
void	init_mutexes(t_arg *args)
{
	int				i;
	int				philos;
	pthread_mutex_t	*forks;

	philos = args->philo_num;
	forks = malloc(sizeof(pthread_mutex_t) * philos);
	i = 0;
	while (i < philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->print_lock, NULL);
	args->forks = forks;
}
