/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:11:32 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 15:04:12 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_struct		p;

	if (parse_args(ac, av) == 0)
		return (0);
	init_args(ac, av, &p);
	p.ph = malloc(sizeof(t_philo) * p.arg.total);
	if (!p.ph)
		return (0);
	if (!initialize(&p))
		return (free(p.ph), 0);
	if (!threading(&p))
		return (free(p.ph), 0);
	return (free_all(&p), 0);
}

// valgrind --leak-check=full
// valgrind --leak-check=full --show-leak-kinds=all

// No one should die tests :
// ./philo 2 800 200 200 
// ./philo 5 800 200 200 
// ./philo 10 800 300 300 
// ./philo 4 410 200 200 
// ./philo 4 2147483647 200 200 (INTMAX test)
// ./philo 5 800 200 200 7 (sim stops when 7 meals are eaten by each philo)

// One should die tests :
// ./philo 4 310 200 100
// ./philo 1 200 200 200
// ./philo 2 400 200 201
// ./philo 2 400 201 100

// Invalid input tests :
// ./philo 0 800 200 200 (0 philo)
// ./philo -1 800 200 200 (negative number)
// ./philo 1 900 -200 200 (negative number)
// ./philo 1 2147483648 200 200 (INTMAX + 1)
// ./philo 1 18446744073709551615 200 200 (ULLONG_MAX)
// ./philo 1 800 200 20A (non digit)
// ./philo 1 800 200 200 7 500 (too many args)
// ./philo 1 800 200 (too few args)