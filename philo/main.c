/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:28:02 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/04 15:53:23 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

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

void	free_struct(t_p *p)
{
	int	i;

	i = -1;
	while (!check_death2(p))
		ft_usleep(1);
	while (++i < p->a.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->a.write_mutex);
	i = -1;
	while (++i < p->a.total)
		pthread_mutex_destroy(&p->ph[i].l_f);
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
	if (!initialize(&p) || !threading(&p))
	{
		free(p.ph);
		return (0);
	}
	free_struct(&p);
	return (1);
}
