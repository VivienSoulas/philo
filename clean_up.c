/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:41:54 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/03 15:36:18 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean_table(t_table *table, int forks)
{
	while (forks >= 0)
	{
		pthread_mutex_destroy(&table->forks[forks]);
		forks--;
	}
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->full_mutex);
	free(table->forks);
	table->forks = NULL;
}

void	ft_clean_philos(t_philo *philos, int count)
{
	while (count >= 0)
	{
		if (pthread_join(philos[count].thread, NULL) != 0)
			write(2, "Error: failed to join philosopher thread\n", 42);
		count--;
	}
	free(philos);
	philos = NULL;
}

void	ft_clean_all(t_philo *philos, t_table *table)
{
	ft_clean_philos(philos, table->n_philo);
	ft_clean_table(table, table->n_philo);
	free(table);
	table = NULL;
}
