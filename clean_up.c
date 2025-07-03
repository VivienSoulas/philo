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
}

void	ft_clean_all(t_philo *philos, t_table *table)
{
	ft_clean_philos(philos, table->n_philo);
	ft_clean_table(table, table->n_philo);
	free(table);
	free(philos);
}
