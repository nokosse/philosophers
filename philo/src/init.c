/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:58 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 14:50:37 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_args(int argc, char **argv, t_struct *p)
{
	p->arg.total = ft_atoi(argv[1]);
	p->arg.die = ft_atoi(argv[2]);
	p->arg.eat = ft_atoi(argv[3]);
	p->arg.sleep = ft_atoi(argv[4]);
	p->arg.meals_to_eat = -1;
	if (argc == 6)
		p->arg.meals_to_eat = ft_atoi(argv[5]);
}

void	init_mutex(t_struct *p)
{
	pthread_mutex_init(&p->arg.mutex_print, NULL);
	pthread_mutex_init(&p->arg.dead, NULL);
	pthread_mutex_init(&p->arg.time_eat, NULL);
	pthread_mutex_init(&p->arg.finish, NULL);
}

int	initialize(t_struct *p)
{
	int	i;

	i = 0;
	p->arg.start_t = actual_time();
	p->arg.stop = 0;
	p->arg.satiated_philos = 0;
	init_mutex(p);
	while (i < p->arg.total)
	{
		p->ph[i].id = i + 1;
		p->ph[i].last_eat = p->arg.start_t;
		p->ph[i].nb_eat = 0;
		p->ph[i].finish = 0;
		p->ph[i].right_fork = NULL;
		pthread_mutex_init(&p->ph[i].left_fork, NULL);
		if (p->arg.total == 1)
			return (1);
		if (i == p->arg.total - 1)
			p->ph[i].right_fork = &p->ph[0].left_fork;
		else
			p->ph[i].right_fork = &p->ph[i + 1].left_fork;
		i++;
	}
	return (1);
}

void	free_all(t_struct *p)
{
	int	i;

	i = 0;
	while (p->arg.stop == 0)
		ft_usleep(1);
	while (i < p->arg.total)
	{
		pthread_join(p->ph[i].thread_id, NULL);
		i++;
	}
	pthread_mutex_destroy(&p->arg.mutex_print);
	i = 0;
	while (i < p->arg.total)
	{
		pthread_mutex_destroy(&p->ph[i].left_fork);
		i++;
	}
	free(p->ph);
}
