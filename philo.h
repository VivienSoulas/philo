/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:24:00 by vsoulas           #+#    #+#             */
/*   Updated: 2025/06/27 17:29:12 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>


typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	struct timeval	start_time;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int				death;
	int				finished_eating;
}	t_table;

// struct for the philo parameters, max philo 200
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				index;
	int				left_fork;
	int				right_fork;
	struct timeval	last_meal;
	int				meals_eaten;
	t_table			*table;
}	t_philo;

typedef struct s_monitor_data
{
	pthread_t	monitor;
	t_table		*table;
	t_philo		*philo;
}	t_monitor_data;

// main
t_philo			*ft_create_philos(t_table *table);
t_monitor_data	*ft_create_monitor(t_philo *philo, t_table *table);

// table
int				ft_set_table(t_table *table, struct timeval start, char **av);
void			ft_initialise_table(t_table *table, struct timeval start, char **av);
int				ft_init_forks(t_table *table);

// clean up
void			ft_clean_table(t_table *table, int forks);
void			ft_clean_philos(t_philo *philos, int count);

// utils
int				ft_check_input(char **av);
int				ft_atoi(char *s1);
long			ft_get_time(struct timeval start_time);

// routine
void			*routine(void *philo);
void			*monitor_routine(void *philos);

#endif