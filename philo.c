/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:23:56 by vsoulas           #+#    #+#             */
/*   Updated: 2025/06/27 16:24:13 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table			*table;
	t_philo			*philosophers;
	t_monitor_data	*monitor_data;
	struct timeval	start_time;

	if (ac > 6 || ac < 5)
	{
		write(2, "Philo: Invalid number of arg\n", 30);
		return (1);
	}
	if (ft_check_input(av) == 1)
		return (1);
	gettimeofday(&start_time, NULL);


	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (1);
	if (ft_set_table(table, start_time, av) == 1)
		return (free(table), 1);
	philosophers = ft_create_philos(table);
	if (philosophers == NULL)
		return (ft_clean_table(table, table->n_philo), free(table), 1);
	monitor_data = ft_create_monitor(philosophers, table);
	if (monitor_data == NULL)
		return (ft_clean_table(table, table->n_philo), free(table), 1);
	// philosophers to clean + free(philosophers)


	return (ft_clean_table(table, table->n_philo), free(table), 0); // free philosophers, free monitor_data
}

t_monitor_data	*ft_create_monitor(t_philo *philo, t_table *table)
{
	t_monitor_data	*monitor_data;

	monitor_data = malloc(sizeof(t_monitor_data));
	if (monitor_data == NULL)
		return (NULL);
	monitor_data->philo = philo;
	monitor_data->table = table;
	if (pthread_create(&monitor_data->monitor,
			NULL, &monitor_routine, monitor_data) != 0)
		return (free(monitor_data), NULL);
	return (monitor_data);
}

// creates as many threads as philosophers requeste
// one more thread for monitoring purpose
// in order to start the philolsopher on 1 instead of 0
//	we add + 1 to philosopher index
// philo[i].philo = philo --> in order to find the forks in routine
t_philo	*ft_create_philos(t_table *table)
{
	int			i;
	t_philo		*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * table->n_philo);
	if (philos == NULL)
		return (NULL);
	while (i < table->n_philo)
	{
		philos[i].id = i;
		philos[i].index = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % table->n_philo;
		philos[i]. last_meal = table->start_time;
		philos[i].meals_eaten = 0;
		philos[i].table = table;
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (ft_clean_philos(philos, i), NULL);
		i++;
	}
	return (philos);
}
