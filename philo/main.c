/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:11:32 by kvisouth          #+#    #+#             */
/*   Updated: 2023/09/14 15:06:28 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// We malloc only philo because there is threads in this structure (t_philo),
// and threads need to be malloced but mutexes don't need to be malloced.

// KNOWN ISSUE : Potential deadlock (fsanitize) / lock order violated (helgrind)
int	main(int ac, char **av)
{
	t_struct		st;

	if (parse_args(ac, av) == 0)
		return (0);
	init_arg(ac, av, &st);
	st.philo = malloc(sizeof(t_philo) * st.arg.nb_philo);
	if (!st.philo)
		return (0);
	init_philo(&st);
	if (!threading(&st))
		return (free(st.philo), 0);
	return (free_all(&st), 0);
}

// Valgrind tests might skew the results because it is running the simulation
// much much slower than usual, making philos dying sometimes.
// Use valgrind only to check leaks and not to compare the results !
// valgrind --leak-check=full
// valgrind --leak-check=full --show-leak-kinds=all

// ./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> <nb_meals>

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