/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_think.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:37:24 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 14:53:50 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_lock);
	printf("%ldms philo[%d] is thinking 🤔\n",
		time_ms() - philo->start, philo->id + 1);
	pthread_mutex_unlock(&philo->print_lock);
}
