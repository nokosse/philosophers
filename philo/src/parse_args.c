/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:45:55 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 18:54:03 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// The error message is printed when the arguments are invalid.
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

// This function check if all the arguments of ./philo are valid.
// It first checks if there is 4 or 5 arguments.
// Then it checks if all the arguments are digits.
int	valid_args_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (av[i])
	{
		if (ft_isdigit(av[i][0]) == 0)
			return (0);
		else
		{
			j = 0;
			while (av[i][j])
			{
				if (ft_isdigit(av[i][j]) == 0)
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

// This function will check if all the arguments are larger than INT_MAX.
// If they are, it will return 0.
// The arguments are already checked to be digits, so we can use atoi or atol.
int	check_int_max(char **av)
{
	int		i;
	long	nb;

	i = 1;
	while (av[i])
	{
		nb = ft_atol(av[i]);
		if (nb > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}
