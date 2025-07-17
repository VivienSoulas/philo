/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:24:03 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/11 14:10:09 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_input(char **av)
{
	int	check;

	check = ft_atoi(av[1]);
	if (check == -1 || check == 0)
		return (write(2, "Philo: invalid number of philosophers\n", 38), 1);
	check = ft_atoi(av[2]);
	if (check == -1)
		return (write(2, "Philo: invalid time to die\n", 28), 1);
	check = ft_atoi(av[3]);
	if (check == -1)
		return (write(2, "Philo: invalid time to eat\n", 28), 1);
	check = ft_atoi(av[4]);
	if (check == -1)
		return (write(2, "Philo: invalid time to sleep\n", 30), 1);
	if (av[5])
	{
		check = ft_atoi(av[5]);
		if (check == -1)
			return (write(2, "Philo: invalid number of time to eat\n", 38), 1);
	}
	check = ft_atoi(av[1]);
	if (check == 1)
		return (printf("0 1 died\n"), 1);
	return (0);
}

// modified atoi to check for negative and non numerical input
int	ft_atoi(char *s1)
{
	int	i;
	int	n;
	int	sign;

	n = 0;
	i = 0;
	sign = 1;
	if (s1[i] == '+')
		i++;
	while (s1[i] >= '0' && s1[i] <= '9')
	{
		n = n * 10 + (s1[i] - '0');
		i++;
	}
	if (s1[i])
		return (-1);
	return (n * sign);
}

void	ft_print(long ms, int index, int message, t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->table->death_mutex);
	is_dead = philo->table->death;
	pthread_mutex_unlock(&philo->table->death_mutex);
	if (is_dead == 0)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		if (message == TAKING_FORK)
			printf("%ld %d has taken a fork\n", ms, index);
		else if (message == EATING)
			printf("%ld %d is eating\n", ms, index);
		else if (message == SLEEPING)
			printf("%ld %d is sleeping\n", ms, index);
		else if (message == THINKING)
			printf("%ld %d is thinking\n", ms, index);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	if (message == DEAD)
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d died\n", ms, index);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

void	ft_update(t_philo *phi, t_table *table, int i, int *all_full)
{
	pthread_mutex_lock(&table->meal_mutex);
	if (phi[i].full == 1 && phi[i].check == 0)
	{
		phi[i].check = 1;
		(*all_full)++;
	}
	pthread_mutex_unlock(&table->meal_mutex);
}
