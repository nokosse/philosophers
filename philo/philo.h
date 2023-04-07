/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:37:00 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/07 14:02:54 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "notlibft/inc/notlibft.h"
# include <sys/time.h>
# include <pthread.h>

int	valid_args_check(int ac, char **av);

#endif