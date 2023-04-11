/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/11 14:54:30 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Why not ?
void	invalid_args_msg(void)
{
	printf("Error	: Invalid arguments\n\n");
	printf("Usage	: ./philo arg1 arg2 arg3 arg4 (arg5)\n");
	printf("arg1 	: 🚹number_of_philosophers\n");
	printf("arg2	: 💀time_to_die (ms)\n");
	printf("arg3	: 🍝time_to_eat (ms)\n");
	printf("arg4	: 💤time_to_sleep (ms)\n");
	printf("(arg5)	: number_of_times_each_philosopher_must_eat\n\n");
	printf("Example	: ./philo 5 800 200 200\n");
	printf("Example	: ./philo 5 800 200 200 7\n");
}

int	main(int ac, char **av)
{
	if (!valid_args_check(ac, av) || !check_int_max(av))
		return (invalid_args_msg(), 0);
	printf("Correct arguments\n");
	return (1);
}
