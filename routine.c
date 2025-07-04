/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:27:11 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/03 16:09:56 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philos)
{
	t_philo			*philo;
	t_table			*table;

	philo = (t_philo *)philos;
	table = philo->table;
	while (1)
	{
		if (ft_routine_loop(philo) == 1)
			break ;
	}
	return (NULL);
}

int	ft_routine_loop(t_philo *philo)
{
	int	first;
	int	second;

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
		return (1);
	}
	if (philo->table->death == 1)
		return (1);
	return (0);
}

void	*monitor_routine(void *monitor_datas)
{
	t_monitor_data	*monitor_data;
	t_philo			*philo;
	t_table			*table;
	int				i;
	int				all_full;

	monitor_data = monitor_datas;
	philo = monitor_data->philo;
	table = monitor_data->table;
	all_full = 0;
	while (1)
	{
		i = -1;
		all_full = ft_moni_loop(i, table, all_full, philo);
		if (all_full == table->n_philo)
		{
			pthread_mutex_lock(&table->full_mutex);
			table->full = 1;
			pthread_mutex_unlock(&table->full_mutex);
			return (NULL);
		}
		else if (all_full == -1)
			return (NULL);
	}
	return (NULL);
}

int	ft_moni_loop(int i, t_table *table, int all_full, t_philo *phi)
{
	int				time_past;
	struct timeval	now;
	long			ms;

	while (++i < table->n_philo)
	{
		gettimeofday(&now, NULL);
		time_past = (now.tv_sec - phi[i].last_meal.tv_sec) * 1000
			+ (now.tv_usec - phi[i].last_meal.tv_usec) / 1000;
		if (time_past > table->t_die)
		{
			ms = ft_get_time(phi->table->start_time);
			ft_print(ms, phi->index, DEAD, phi);
			pthread_mutex_lock(&table->death_mutex);
			table->death = 1;
			pthread_mutex_unlock(&table->death_mutex);
			return (-1);
		}
		ft_update(phi, table, i, all_full);
	}
	return (all_full);
}

void	ft_philosophing(t_philo *philo, int first, int second)
{
	long	ms;

	pthread_mutex_lock(&philo->table->forks[first]);
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, TAKING_FORK, philo);
	pthread_mutex_lock(&philo->table->forks[second]);
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, TAKING_FORK, philo);
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, EATING, philo);
	usleep(philo->table->t_eat * 1000);
	gettimeofday(&philo->last_meal, NULL);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->forks[first]);
	pthread_mutex_unlock(&philo->table->forks[second]);
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, SLEEPING, philo);
	usleep(philo->table->t_sleep * 1000);
	ms = ft_get_time(philo->table->start_time);
	ft_print(ms, philo->index, THINKING, philo);
}
