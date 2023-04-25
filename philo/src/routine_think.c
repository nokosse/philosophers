/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_think.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:47:21 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 18:13:13 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Philo will think for time_to_think ms
void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ldms philo[%d] 🤔💭 is thinking\n", \
		ft_time() - philo->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->lock_print);
}
