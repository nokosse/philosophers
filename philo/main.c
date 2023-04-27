/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/27 13:53:37 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_arg	args;

	if (!valid_args_check(ac, av) || !check_int_max(av))
		return (invalid_args_msg(), 0);
	if (init_args(&args, ac, av) == 1)
		return (0);
	init_mutexes(&args);
	init_philos(&args);
	init_threads(&args);
	kill_threads(&args);
	kill_mutexes(&args);
	free_args(&args);
	return (1);
}
