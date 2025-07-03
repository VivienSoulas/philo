/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:27:11 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/03 14:53:08 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philosophing(t_philo *philo, int first, int second)
{
	long	ms;
// eating
	// takes a fork
	pthread_mutex_lock(&philo->table->forks[first]);
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, TAKING_FORK, philo);
	
	// takes a second fork
	pthread_mutex_lock(&philo->table->forks[second]);
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, TAKING_FORK, philo);

	// eats
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, EATING, philo);
	//time to eat
	usleep(philo->table->t_eat * 1000);
	// update last meal time and total of meal eaten
	gettimeofday(&philo->last_meal, NULL);
	philo->meals_eaten++;

	// drop forks
	pthread_mutex_unlock(&philo->table->forks[first]);
	//ft_print(ms, philo->index, DROPPED, philo);
	pthread_mutex_unlock(&philo->table->forks[second]);
	//ft_print(ms, philo->index, DROPPED, philo);

// sleeping
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, SLEEPING, philo);
	usleep(philo->table->t_sleep * 1000);
	
// thinking
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, THINKING, philo);
}

void	*routine(void *philos)
{
	t_philo			*philo;
	t_table			*table;
	int				first;
	int				second;

	philo = (t_philo *)philos;
	table = philo->table;
	while (1)
	{
		if (philo->index % 2)
		{
			first = philo->left_fork;
			second = philo->right_fork;
		}
		else
		{
			first = philo->right_fork;
			second = philo->left_fork;
		}
		ft_philosophing(philo, first, second);
		if (philo->table->n_meals > 0
			&& philo->meals_eaten == philo->table->n_meals)
		{
			philo->full = 1;
			break ;
		}
		if (philo->table->death == 1)
			break ;
	}
	return (printf("exiting thread\n"), NULL);
}

void	*monitor_routine(void *monitor_datas)
{
	t_monitor_data	*monitor_data;
	t_philo			*philo;
	t_table			*table;
	int				i;
	int				all_full;
	struct timeval	now;
	int				time_past;

	monitor_data = monitor_datas;
	philo = monitor_data->philo;
	table = monitor_data->table;
	all_full = 0;
	while (1)
	{
//check for death
		i = 0;
		while (i < table->n_philo)
		{
			gettimeofday(&now, NULL);
			time_past = (now.tv_sec - philo[i].last_meal.tv_sec) * 1000
				+ (now.tv_usec - philo[i].last_meal.tv_usec) / 1000;
			if (time_past > table->t_die)
			{
				long ms = ft_get_time(philo->table->start_time);
				ft_print(ms, philo->index, DEAD, philo);
				//pthread_mutex_lock(&table->death_mutex);
				table->death = 1;
				//pthread_mutex_unlock(&table->death_mutex);
				return (NULL);
			}
			if (philo[i].full == 1 && philo[i].check == 0)
			{
				pthread_mutex_lock(&table->full_mutex);
				philo[i].check = 1;
				all_full++;
				pthread_mutex_unlock(&table->full_mutex);
			}
			i++;
		}
		if (all_full == table->n_philo)
		{
			pthread_mutex_lock(&table->full_mutex);
			table->full = 1;
			//usleep(100);
			pthread_mutex_unlock(&table->full_mutex);
			printf("fulllllllllllllll\n");
			return (NULL);
		}
	}
	
	return (NULL);
}
