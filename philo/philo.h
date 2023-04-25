/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:37:00 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/25 18:33:55 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				total_meals_eaten;
	int				total_meals;
	time_t			last_meal;
	int				total_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	time_t			limit_death;
	int				stop;
	time_t			start_time;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_arg	*arg;
}					t_philo;

typedef struct s_arg
{
	int				total_philos;
	int				id;
	time_t			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_dead;
	int				nbr_of_meals;
	pthread_mutex_t	*forks;
	pthread_t		*threads_id;
	pthread_mutex_t	lock_print;
	t_philo			*philos;
}					t_arg;

// "notlibft" functions
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_isdigit(int c);

// Arguments parsing
int		valid_args_check(int ac, char **av);
int		check_int_max(char **av);

// Philosophers routine
void	taking_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

long	ft_time(void);
int		ft_cnt_of_meals(t_philo *philo);
void	*monitoring(void *args);
void	*ft_process(void *args);
void	init_philos(t_arg *args);
void	init_mutexes(t_arg *args);
void	kill_mutexes(t_arg *args);
void	init_threads(t_arg *args);
void	kill_threads(t_arg *args);
int		init_args(t_arg *args, int argc, char **argv);
void	free_all(t_arg *args);
void	unlock_and_destroy_mutex(t_arg *args);
void	ft_usleep(int ms);

#endif