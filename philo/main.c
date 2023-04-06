/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/06 14:33:55 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function checks if the arguments in main are valid.
// For this project we need 4 or 5 arguments.
// They all must be numbers.
static int	valid_args_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (av[i])
	{
		if (!ft_isdigit_str(av[i]) && !ft_atol(av[i]))
			return (write(2, "Invalid arguments\n", 18), 0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	(void)av;
	int a = ft_strlen(av[1]);
	printf("%d\n", a);
	if (!valid_args_check(ac, av))
		return (1);
	printf("Correct arguments\n");
	return (0);
}
