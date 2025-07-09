/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:43:49 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/03 15:15:56 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			ft_clean_table(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_init_table(t_table *table, struct timeval start, char **av)
{
	table->start_time = start;
	table->n_philo = ft_atoi(av[1]);
	table->t_die = ft_atoi(av[2]);
	table->t_eat = ft_atoi(av[3]);
	table->t_sleep = ft_atoi(av[4]);
	if (av[5])
		table->n_meals = ft_atoi(av[5]);
	else
		table->n_meals = -1;
	table->death = 0;
	table->full = 0;
	table->finished_eating = 0;
}

int	ft_set_table(t_table *table, struct timeval start, char **av)
{
	// int	i;

	// i = 0;
	ft_init_table(table, start, av);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (table->forks == NULL)
		return (1);
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
		return (free(table->forks), 1);
	if (pthread_mutex_init(&table->print_mutex, NULL))
	{
		pthread_mutex_destroy(&table->death_mutex);
		return (free(table->forks), 1);
	}
	if (pthread_mutex_init(&table->full_mutex, NULL))
	{
		pthread_mutex_destroy(&table->death_mutex);
		pthread_mutex_destroy(&table->print_mutex);
		return (free(table->forks), 1);
	}
if (pthread_mutex_init(&table->meals_mutex, NULL))
{
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->full_mutex);
	return (free(table->forks), 1);
}
	if (ft_init_forks(table) == 1)
		return (1);
	return (0);
}
