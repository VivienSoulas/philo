/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:27:11 by vsoulas           #+#    #+#             */
/*   Updated: 2025/06/27 15:36:47 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(struct timeval start_time)
{
	struct timeval	now;
	long			ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec - start_time.tv_sec) * 1000
		+ (now.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}

// we are here using the % in order for the last
//		philosopher to find the first fork on the table
void	*routine(void *philo)
{
	t_philo			*current;
	t_philo			*philos;
	long			ms;

	current = (t_philo *)philo;
	philos = current->philosopher;

	while (1)
	{
		// eating actions
		if (current->id % 2 == 0)
		{
			usleep(2000);
			pthread_mutex_lock(&philos[philos->right].forks);
			pthread_mutex_lock(&philos[philos->left].forks);
		}
		else
		{
			pthread_mutex_lock(&philos[philos->left].forks);
			pthread_mutex_lock(&philos[philos->right].forks);
		}
		ms = ft_get_time(current->start_time);
		printf("%ld %d has taken a fork\n", ms, current->id);
		ms = ft_get_time(current->start_time);

		printf("%ld %d is eating\n", ms, current->id);
		usleep(current->time_to_eat * 1000);

		gettimeofday(&current->last_meal, NULL);
		current->meals_eaten++;

		pthread_mutex_unlock(&philos[philos->left].forks);
		pthread_mutex_unlock(&philos[philos->right].forks);

		// sleeping ation
		ms = ft_get_time(current->start_time);
		printf("%ld %d is sleeping\n", ms, current->id);
		usleep(current->time_to_sleep * 1000);

		// thinking action
		ms = ft_get_time(current->start_time);
		printf("%ld %d is thinking\n", ms, current->id);

		if (current->number_of_time_each_philosopher_must_eat > 0
			&& current->meals_eaten == current->number_of_time_each_philosopher_must_eat)
			break ;
	}
	return (NULL);
}

void	*monitor_routine(void *philos)
{
	struct timeval	now;
	t_philo			*philo;
	long			time_past;
	long			ms;
	int				i;

	philo = (t_philo *)philos;
	while (1)
	{
		i = 0;
		while (i < philo[0].number_of_philosophers)
		{
			gettimeofday(&now, NULL);
			time_past = (now.tv_sec - philo[i].last_meal.tv_sec) * 1000
				+ (now.tv_usec - philo[i].last_meal.tv_usec) / 1000;
			if (time_past > philo[i].time_to_die)
			{
				ms = ft_get_time(philo[i].start_time);
				printf("%ld %d died\n", ms, philo[i].id);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
