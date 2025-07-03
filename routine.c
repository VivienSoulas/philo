/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:27:11 by vsoulas           #+#    #+#             */
/*   Updated: 2025/06/27 17:34:12 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// we are here using the % in order for the last
//		philosopher to find the first fork on the table
void	*routine(void *philo)
{
	t_philo			*current;
	t_philo			*philos;
	long			ms;
	int				first;
	int				second;

	current = (t_philo *)philo;
	philos = current->philosopher;
	usleep((current->id % 2) * 100);
	while (philos->time_to_die < 0)
	{
		// printf("%d time to die ======== %d\n", current->id, current->time_to_die);
		// if (current->time_to_die < 0)
		// {
		// 	printf("======================\n");
		// 	break ;
		// }
		// eating actions
		if (current->left < current->right)
		{
			first = current->left;
			second = current->right;
		}
		else
		{
			first = current->right;
			second = current->left;
		}
		pthread_mutex_lock(&philos[first].forks);
		ms = ft_get_time(current->start_time);
		printf("%ld %d has taken a fork\n", ms, current->id);

		pthread_mutex_lock(&philos[second].forks);
		ms = ft_get_time(current->start_time);
		printf("%ld %d has taken a fork\n", ms, current->id);
		ms = ft_get_time(current->start_time);

		printf("%ld %d is eating\n", ms, current->id);
		usleep(current->time_to_eat * 1000);

		gettimeofday(&current->last_meal, NULL);
		current->meals_eaten++;

		pthread_mutex_unlock(&philos[first].forks);
		pthread_mutex_unlock(&philos[second].forks);

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
				int j = 0;
				while (j < philo[0].number_of_philosophers)
				{
					philo[j].time_to_die = -1;
					j++;
				}
				ms = ft_get_time(philo[i].start_time);
				printf("%ld %d died\n", ms, philo[i].id);
				return (NULL);
			}
			i++;
		}
		usleep(50);
	}
	return (NULL);
}
