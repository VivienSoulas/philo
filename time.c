/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:08:12 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/11 14:29:09 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

long	ft_get_time(struct timeval start_time)
{
	struct timeval	now;
	long			ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec - start_time.tv_sec) * 1000
		+ (now.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}

void	ft_sleep(int i, t_philo *philo)
{
	long	ms;
	long	time_to_wake;
	int		is_dead;

	ms = ft_get_time(philo->table->start_time);
	if (i == EATING)
	{
		time_to_wake = ms + philo->table->t_eat;
		while (time_to_wake > ms)
		{
			usleep(50);
			pthread_mutex_lock(&philo->table->death_mutex);
			is_dead = philo->table->death;
			pthread_mutex_unlock(&philo->table->death_mutex);
			if (is_dead == 1)
				return ;
			ms = ft_get_time(philo->table->start_time);
		}
	}
	if (i == SLEEPING)
	{
		time_to_wake = ms + philo->table->t_sleep;
		while (time_to_wake > ms)
		{
			usleep(50);
			pthread_mutex_lock(&philo->table->death_mutex);
			is_dead = philo->table->death;
			pthread_mutex_unlock(&philo->table->death_mutex);
			if (is_dead == 1)
				return ;
			ms = ft_get_time(philo->table->start_time);
		}
	}
}
