/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:52:18 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/04 11:07:09 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_mutex_lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philos[philo->id].fork);
	printf("%lld ph %d as taken a fork\n", (timems() - philo->data->start), philo->id);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->data->philos[philo->data->ph_nb - 1].fork);
	else
		pthread_mutex_lock(&philo->data->philos[philo->id - 1].fork);
}

void	ft_mutex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->philos[philo->id].fork);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->data->philos[philo->data->ph_nb - 1].fork);
	else
		pthread_mutex_unlock(&philo->data->philos[philo->id - 1].fork);
}

void	sleeping(t_philo *philo)
{
	printf("%lld ph %d is sleeping\n", (timems() - philo->data->start), philo->id);
	ft_usleep(philo->data->sleep);
}

void	thinking(t_philo *philo)
{
	printf("%lld ph %d is thinking\n", (timems() - philo->data->start), philo->id);
}

int	check_eats(t_philo *philo)
{
	if (philo->eats == philo->data->eat_nb)
	{
		philo->data->philos[philo->id].running = 0;
		philo->data->eats_done++;
		return (1);
	}
	return (0);
}
