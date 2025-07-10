/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:24:00 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/03 16:03:53 by vsoulas          ###   ########.fr       */
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

// defines for messages
# define TAKING_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DROPPED 4
# define DEAD 5

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	print_mutex;
	struct timeval	start_time;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int				death;
	int				full;
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
	int				meals_eaten;
	int				full;
	int				check;
	struct timeval	last_meal;
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
void			ft_join_threads(t_philo *philo, t_monitor_data *monitor_data);

// table
int				ft_set_table(t_table *table, struct timeval start, char **av);
void			ft_init_table(t_table *table, struct timeval start, char **av);
int				ft_init_forks(t_table *table);

// routine
void			*routine(void *philo);
int				ft_routine_loop(t_philo *philo);
void			*monitor_routine(void *monitor_datas);
int				ft_moni_loop(int i, t_table *table, int *all_full, t_philo *phi);
void			ft_philosophing(t_philo *philo, int first, int second);

// clean up
void			ft_clean_table(t_table *table, int forks);
void			ft_clean_philos(t_philo *philos, int count);
void			ft_clean_all(t_philo *philos, t_table *table);

// utils
int				ft_check_input(char **av);
int				ft_atoi(char *s1);
long			ft_get_time(struct timeval start_time);
void			ft_print(long ms, int index, int message, t_philo *philo);
void			ft_update(t_philo *phi, t_table *table, int i, int *all_full);

#endif