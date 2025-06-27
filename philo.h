#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

// struct for the philo parameters, max philo 200
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	forks;
	struct timeval	start_time;
	int				id;
	int				index;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_each_philosopher_must_eat;
	struct s_philo	*philos;
}	t_philo;

// philo
t_philo	*ft_create_threads(int number_of_philosophers, char **av, struct timeval start);
int		ft_join_threads(t_philo *philo, int number_of_philosophers);

// utils
int		ft_check_input(char **av);
int		ft_atoi(char *s1);
int		ft_initialise_philo(t_philo *philo, char **av, struct timeval start);

#endif