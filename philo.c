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
	t_philo			*philo;
	pthread_t		monitor;	
	int			 	number_of_philosophers;
	struct timeval	start_time;

	if (ac > 6 || ac < 5)
	{
		write(2, "Philo: Invalid number of arg\n", 30);
		return (1);
	}
	if (ft_check_input(av) == 1)
		return (1);
	gettimeofday(&start_time, NULL);
	number_of_philosophers = ft_atoi(av[1]);
	philo = ft_create_threads(number_of_philosophers, av, start_time);
	if (philo == NULL)
		return (write(2, "Philo: malloc fail\n", 20), 1);

	if (pthread_create(&monitor, NULL, &monitor_routine, philo) != 0)
		return (free(philo), write(2, "FAILED creating monitor thread", 32), 1);

	if (ft_join_threads(monitor, philo, number_of_philosophers) == 1)
		return (free(philo), 3);



	return (free(philo), 0);
}

// creates as many threads as philosophers requeste
// one more thread for monitoring purpose
// in order to start the philolsopher on 1 instead of 0
//	we add + 1 to philosopher index
// philo[i].philo = philo --> in order to find the forks in routine
t_philo	*ft_create_threads(int number_of_phil, char **av, struct timeval start)
{
	int			i;
	t_philo		*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * number_of_phil);
	if (philos == NULL)
		return (NULL);
	while (i < number_of_phil)
	{
		philos[i].index = i;
		philos[i].id = i + 1;
		philos[i].philosopher = philos;
		if (ft_initialise_philo(&philos[i], av, start) == 1)
			return (free(philos), NULL);
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			write(2, "FAILED creating threads", 24);
			return (free(philos), NULL);
		}
		i++;
	}
	return (philos);
}

int	ft_join_threads(pthread_t monitor, t_philo *philo, int number_of_philo)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < number_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			write(2, "FAILED joining philosopher", 27);
			error = 1;
		}
		i++;
	}
	i = 0;
	while (i < number_of_philo)
	{
		pthread_mutex_destroy(&philo[i].forks);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
	{
		write(2, "FAILED joining monitor thread", 30);
		error = 1;
	}
	return (error);
}
