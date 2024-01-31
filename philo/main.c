/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:11:32 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/31 15:00:08 by kvisouth         ###   ########.fr       */
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
