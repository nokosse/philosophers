/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:37:00 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/14 15:05:20 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "notlibft/inc/notlibft.h"
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

// The struture to store the arguments of ./philo
// With some other variables to be used in the program
typedef struct s_arg
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int 			meals_num;
	int				is_dead;
	time_t			start_time;
	int				philo_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
}					t_arg;

// The structure to store the philosophers
// With some more useful information on them.
typedef struct s_philo
{
	int		id;
	int		total_meals;
	time_t	last_meal;
	int		total_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}				t_philo;

// Argument check functions
int		valid_args_check(int ac, char **av);
int		check_int_max(char **av);

// Initialization functions
int		init_args(t_arg *args, int ac, char **av);
void	init_mutexes(t_arg *args);


#endif