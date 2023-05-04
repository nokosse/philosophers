/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:42:16 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/04 16:00:24 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// This function checks if the string is numeric only
int	check_numeric(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

// This function checks if the string is positive (> 0)
int	check_positive(char *av)
{
	if (ft_atoi(av) <= 0)
		return (0);
	return (1);
}

// This function checks if the string is less than 11 digits
int	check_ullong(char *av)
{
	if (ft_strlen(av) > 10)
		return (0);
	return (1);
}

// This function checks if the string doesn't exceed INT_MAX
int	check_int_max(char *av)
{
	if (ft_atol(av) > INT_MAX)
		return (0);
	return (1);
}

// This function checks if the arguments are valid.
int	parse_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5)
		return (printf("Error : not enough arguments\n"), 0);
	if (ac > 6)
		return (printf("Error : too many arguments\n"), 0);
	while (i < ac)
	{
		if (!check_numeric(av[i]))
			return (printf("Error : argument %d is not numeric\n", i + 1), 0);
		if (!check_int_max(av[i]))
			return (printf("Error : argument %d is too big\n", i + 1), 0);
		if (!check_ullong(av[i]))
			return (printf("Error : argument %d is too big\n", i + 1), 0);
		if (!check_positive(av[i]))
			return (printf("Error : argument %d is not positive\n", i + 1), 0);
		i++;
	}
	return (1);
}
