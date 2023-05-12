/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:07:36 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/12 16:27:22 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Libraries

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

// Structures

// Structure for arguments (t_arg)
// It will store most of the arguments we send.
typedef struct s_arg
{
	int						nb_philo;
	int						time2die;
	int						time2eat;
	int						time2sleep;
	int						meals_to_eat;
	int						satiated_philos;
	int						flag;
	long int				time_start;
	pthread_mutex_t			mutex_print;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
}							t_arg;

// Structure for philosophers (t_philo)
// It will store the information of each philosopher.
//
// There is 2 threads in the program :
// thread_id: Each philos is represented by a thread, this is the thread.
// thread_death_id: It's the monitoring thread, it's checking the death status.
//
// There is also 2 mutexes, which are the forks of the philos.
typedef struct s_philo
{
	int						id;
	int						finish;
	long int				last_eat;
	unsigned int			nb_eat;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	t_arg					*sarg;
}							t_philo;

// Structure for the program (t_struct)
// It will store both structures above to have an easy access to them.
typedef struct s_struct
{
	t_philo					*philo;
	t_arg					arg;
}							t_struct;

// Parsing
int				parse_args(int ac, char **av);

// Initialization
int				init_philo(t_struct *st);
void			init_arg(int argc, char **argv, t_struct *st);
void			free_all(t_struct *st);

// Functions
int				threading(t_struct *st);
int				check_death(t_philo *philo, int i);
void			routine(t_philo *philo);
void			dying(t_philo *philo);
void			thinking(t_philo *philo);
void			sleeping(t_philo *philo);
void			eating(t_philo *philo);
void			print_status(char *str, t_philo *philo);

// Lib & Utils
int				ft_strlen(char *str);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			ft_usleep(long int time_in_ms);
long			ft_atol(const char *str);
long			actual_time(void);

#endif