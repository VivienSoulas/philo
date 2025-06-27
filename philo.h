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

// struct for the philo parameters, max philo 200
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	forks;
	struct timeval	start_time;
	struct timeval	now;
	struct timeval	last_meal;
	int				meals_eaten;
	int				id;
	int				index;
	int				left;
	int				right;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_each_philosopher_must_eat;
	struct s_philo	*philosopher;
}	t_philo;

// philo
t_philo	*ft_create_threads(int number_of_phil, char **av, struct timeval start);
int		ft_join_threads(pthread_t monitor, t_philo *philo, int number_of_philo);

// routine
void	*routine(void *philo);
void	*monitor_routine(void *philos);

// utils
int		ft_check_input(char **av);
int		ft_atoi(char *s1);
int		ft_initialise_philo(t_philo *philo, char **av, struct timeval start);

#endif