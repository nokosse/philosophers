/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_sleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:36:46 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 14:59:35 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_lock);
	printf("%ldms philo[%d] is sleeping 💤\n",
		time_ms() - philo->start, philo->id + 1);
	pthread_mutex_unlock(&philo->print_lock);
	ft_usleep(philo->time_to_sleep);
}
