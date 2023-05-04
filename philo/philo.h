/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:53:13 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/04 16:07:42 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** libraries
*/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/*
** structures
*/

typedef struct s_arg
{
	int						total;
	int						die;
	int						eat;
	int						sleep;
	int						m_eat;
	long int				start_t;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
	int						nb_p_finish;
	int						stop;
}							t_arg;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*r_f;
	pthread_mutex_t			l_f;
	t_arg					*pa;
	long int				ms_eat;
	unsigned int			nb_eat;
	int						finish;
}							t_philo;

typedef struct s_p
{
	t_philo					*ph;
	t_arg					a;
}							t_p;

/*
** functions
*/
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
int				ft_isdigit(int c);
int				parse_args(int ac, char **av);

void			init_args(int argc, char **argv, t_p *p);
int				init_mutex(t_p *p);
int				ft_exit(char *str);
void			write_status(char *str, t_philo *ph);
long int		actual_time(void);
void			ft_putstr_fd(char *s, int fd);
void			ft_usleep(long int time_in_ms);

int				threading(t_p *p);

void			activity(t_philo *ph);
int				check_death(t_philo *ph, int i);
int				ft_strlen(char *str);

#endif