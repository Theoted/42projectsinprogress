/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:01:31 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/04 15:34:48 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(int time)
{
	long long int start;
	long long int end;
	
	start = timems();
	end = timems();
	while (end - start < time)
	{
		usleep(100);
		end = timems();
	}
}

int	check_for_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->speak);
	if (philo->data->ph_dead == 1 || philo->data->check_eat == 1)
	{
		pthread_mutex_unlock(&philo->data->speak);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->speak);
	return (0);
}

int	one_philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philos[philo->id].fork);
	printf("%lld %d as taken a fork\n", (timems() - philo->data->start), philo->id + 1);
	ft_usleep(philo->data->die);
	pthread_mutex_unlock(&philo->data->philos[philo->id].fork);
	return (0);
}
