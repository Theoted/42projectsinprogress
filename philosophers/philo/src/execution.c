/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:52:18 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/07 16:38:09 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	fork_and_eat(t_philo *philo)
{
	if (check_for_end(philo))
		return (1);
	pthread_mutex_lock(&philo->data->philos[philo->id].fork);
	print_out(philo->id + 1, "has taken a fork", philo);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->data->philos[philo->data->ph_nb - 1].fork);
	else
		pthread_mutex_lock(&philo->data->philos[philo->id - 1].fork);
	print_out(philo->id + 1, "has taken a fork", philo);
	print_out(philo->id + 1, "is eating", philo);
	ft_usleep(philo->data->eat, philo);
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
	print_out(philo->id + 1, "is sleeping", philo);
	ft_usleep(philo->data->sleep, philo);
	return (0);
}

int	thinking(t_philo *philo)
{
	print_out(philo->id + 1, "is thinking", philo);
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
