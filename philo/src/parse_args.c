/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:45:55 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/07 14:02:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function check if all the arguments of ./philo are valid.
// It first checks if there is 4 or 5 arguments.
// Then it checks if all the arguments are digits.
int	valid_args_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (write(2, "Invalid arguments\n", 18), 0);
	while (av[i])
	{
		if (ft_isdigit(av[i][0]) == 0)
			return (write(2, "Invalid arguments\n", 18), 0);
		else
		{
			j = 0;
			while (av[i][j])
			{
				if (ft_isdigit(av[i][j]) == 0)
					return (write(2, "Invalid arguments\n", 18), 0);
				j++;
			}
		}
		i++;
	}
	return (1);
}