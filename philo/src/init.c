/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:46:04 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/04 17:45:54 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_args(int argc, char **argv, t_p *p)
{
	p->a.total = ft_atoi(argv[1]);
	p->a.die = ft_atoi(argv[2]);
	p->a.eat = ft_atoi(argv[3]);
	p->a.sleep = ft_atoi(argv[4]);
	p->a.must_eat = -1;
	if (argc == 6)
		p->a.must_eat = ft_atoi(argv[5]);
}

void	init_mutex2(t_p *p)
{
	pthread_mutex_init(&p->a.lock_print, NULL);
	pthread_mutex_init(&p->a.dead, NULL);
	pthread_mutex_init(&p->a.time_eat, NULL);
	pthread_mutex_init(&p->a.finish, NULL);
}

int	init_mutex(t_p *p)
{
	int	i;

	i = 0;
	p->a.start_t = actual_time();
	p->a.stop = 0;
	p->a.finished_philos = 0;
	init_mutex2(p);
	while (i < p->a.total)
	{
		p->ph[i].id = i + 1;
		p->ph[i].ms_eat = p->a.start_t;
		p->ph[i].nb_eat = 0;
		p->ph[i].finish = 0;
		p->ph[i].r_f = NULL;
		pthread_mutex_init(&p->ph[i].l_f, NULL);
		if (p->a.total == 1)
			return (1);
		if (i == p->a.total - 1)
			p->ph[i].r_f = &p->ph[0].l_f;
		else
			p->ph[i].r_f = &p->ph[i + 1].l_f;
		i++;
	}
	return (1);
}
