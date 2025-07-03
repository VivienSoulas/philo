/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:24:03 by vsoulas           #+#    #+#             */
/*   Updated: 2025/06/27 17:19:57 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_input(char **av)
{
	int	check;

	check = ft_atoi(av[1]);
	if (check == -1 ||  check == 0)
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

long	ft_get_time(struct timeval start_time)
{
	struct timeval	now;
	long			ms;

	gettimeofday(&now, NULL);
	ms = now.tv_sec * 1000000 + now.tv_usec;
	return (ms);
}
