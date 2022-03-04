/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:52:18 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/04 15:26:32 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_mutex_lock(t_philo *philo)
{
	if (check_for_end(philo))
		return (1);
	pthread_mutex_lock(&philo->data->philos[philo->id].fork);
	printf("%lld %d as taken a fork\n", (timems() - philo->data->start), philo->id + 1);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->data->philos[philo->data->ph_nb - 1].fork);
	else
		pthread_mutex_lock(&philo->data->philos[philo->id - 1].fork);
	printf("%lld %d as taken a fork\n", (timems() - philo->data->start), philo->id + 1);
	return (0);
}

void	ft_mutex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->philos[philo->id].fork);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->data->philos[philo->data->ph_nb - 1].fork);
	else
		pthread_mutex_unlock(&philo->data->philos[philo->id - 1].fork);
}

int	sleeping(t_philo *philo)
{	
	if (check_for_end(philo))
		return (1);
	printf("%lld %d is sleeping\n", (timems() - philo->data->start), philo->id + 1);
	ft_usleep(philo->data->sleep);
	return(0);
}

int	thinking(t_philo *philo)
{
	if (check_for_end(philo))
		return (1);
	printf("%lld %d is thinking\n", (timems() - philo->data->start), philo->id + 1);
	return (0);
}

int	check_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->speak);
	if (philo->eats == philo->data->eat_nb)
	{
		philo->data->philos[philo->id].running = 0;
		philo->data->eats_done++;
		pthread_mutex_unlock(&philo->data->speak);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->speak);
	return (0);
}
