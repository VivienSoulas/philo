#include "philo.h"

// we are here using the % in order for the last philosopher to find the first fork on the table
void	*routine(void *philo)
{
	t_philo			*current;
	t_philo			*philos;
	struct timeval	now;
	int				left; // own philosopher fork
	int				right;
	long			ms;
	int				meals;

	meals = 0;
	current = (t_philo *)philo;
	philos = current->philos;
	gettimeofday(&now, NULL);
	ms = (now.tv_sec - current->start_time.tv_sec) / 1000
		+ (now.tv_usec - current->start_time.tv_usec);
	left = current->index;
	right = ((current->index + 1) % current->number_of_philosophers);

	while (1)
	{
		pthread_mutex_lock(&philos[left].forks);
		pthread_mutex_lock(&philos[right].forks);
		printf("%ld %d has taken a fork\n", ms, current->id);
		printf("%ld %d is eating\n", ms, current->id);
		meals++;
		printf("%d had eaten %d meals\n", current->id, meals);
		usleep(current->time_to_eat);
		pthread_mutex_unlock(&philos[left].forks);
		pthread_mutex_unlock(&philos[right].forks);

		printf("%ld %d is sleeping\n", ms, current->id);
		usleep(current->time_to_sleep);
		printf("%ld %d is thinking\n", ms, current->id);

		if (current->number_of_time_each_philosopher_must_eat > 0
			&& meals == current->number_of_time_each_philosopher_must_eat)
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
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


	if (ft_join_threads(philo, number_of_philosophers) == 1)
		return (free(philo), 3);



	return (free(philo), 0);
}

// creates as many threads as philosophers requeste
// to add : one more thread for monitoring purpose
t_philo	*ft_create_threads(int number_of_philosophers, char **av, struct timeval start)
{
	int		i;
	t_philo	*philosophers;

	i = 0;
	philosophers = malloc(sizeof(t_philo) * number_of_philosophers);
	if (philosophers == NULL)
		return (NULL);
	while (i < number_of_philosophers)
	{
		philosophers[i].index = i;
		philosophers[i].id = i + 1; // in order to start the philolsopher on 1 instead of 0
		philosophers[i].philos = philosophers;
		if (ft_initialise_philo(&philosophers[i], av, start) == 1)
			return (free(philosophers), NULL);
		if (pthread_create(&philosophers[i].thread, NULL, &routine, &philosophers[i]) != 0)
			return (free(philosophers), write(2, "FAILED creating threads", 23), NULL);
		printf("Philosopher %d created\n", philosophers[i].id);
		i++;
	}
	return (philosophers);
}

// pthread_join(..., void**)
int	ft_join_threads(t_philo *philo, int number_of_philosophers)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			write(2, "FAILED joining philosopher", 27);
			error = 1;
		}
		else
			printf("Philosopher %d has been joined\n", philo[i].id);
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[i].forks);
		i++;
	}
	return (error);
}
