/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:11:32 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/10 18:51:54 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death2(t_p *p)
{
	pthread_mutex_lock(&p->a.dead);
	if (p->a.stop)
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
	while (!check_death2(p))
		ft_usleep(1);
	while (++i < p->a.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->a.mutex_print);
	i = -1;
	while (++i < p->a.total)
		pthread_mutex_destroy(&p->ph[i].left_fork);
	if (p->a.stop == 2)
		printf("Each philosopher ate %d time(s)\n", p->a.meals_to_eat);
	free(p->ph);
}

int	main(int ac, char **av)
{
	t_p		p;

	if (parse_args(ac, av) == 0)
		return (0);
	init_args(ac, av, &p);
	p.ph = malloc(sizeof(t_philo) * p.a.total);
	if (!p.ph)
		return (0);
	if (!initialize(&p))
		return (free(p.ph), 0);
	if (!threading(&p))
		return (free(p.ph), 0);
	free_all(&p);
}

// valgrind --leak-check=full --show-leak-kinds=all ./philo 2 10 10 10
// valgrind --leak-check=full --show-leak-kinds=all ./philo 1 100 10 10
