/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/09 15:18:17 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check_death was used to check if a philosopher died, then put the flag stop.
// This function works the same way but it doesn't put the flag stop.
// It is juste used to check, that's all so we know when the program can be
// freed.
int	check_death2(t_p *p)
{
	pthread_mutex_lock(&p->a.dead);
	if (p->a.stop != 0)
	{
		pthread_mutex_unlock(&p->a.dead);
		return (1);
	}
	pthread_mutex_unlock(&p->a.dead);
	return (0);
}

void	free_all(t_p *p)
{
	int	i;

	i = -1;
	while (check_death2(p) == 0)
		ft_usleep(1);
	while (++i < p->a.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->a.lock_print);
	i = -1;
	while (++i < p->a.total)
		pthread_mutex_destroy(&p->ph[i].left_fork);
	free(p->ph);
}

int	main(int argc, char **argv)
{
	t_p		p;

	if (!parse_args(argc, argv))
		return (0);
	init_args(argc, argv, &p);
	p.ph = malloc(sizeof(t_philo) * p.a.total);
	if (!p.ph)
		return (0);
	if (!init_mutex(&p) || !threading(&p))
		return (free(p.ph), 0);
	free_all(&p);
	return (1);
}
