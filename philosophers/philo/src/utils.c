/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:01:31 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/23 08:32:49 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(int time, t_philo *philo)
{
	long long int	start;
	long long int	end;

	start = timems();
	end = timems();
	while (end - start < time)
	{
		if (check_for_end(philo))
			return ;
		usleep(500);
		end = timems();
	}
}

int	check_for_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_check);
	if (philo->data->ph_dead == 1 || philo->data->check_eat == 1)
	{
		pthread_mutex_unlock(&philo->data->m_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_check);
	return (0);
}

int	one_philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philos[philo->id].fork);
	printf("%lld %d as taken a fork\n",
		(timems() - philo->data->start), philo->id + 1);
	ft_usleep(philo->data->die, philo);
	pthread_mutex_unlock(&philo->data->philos[philo->id].fork);
	return (0);
}

int	print_out(int id, char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->speak);
	if (check_for_end(philo))
	{
		pthread_mutex_unlock(&philo->data->speak);
		return (1);
	}
	printf("%lld %d %s\n", timems() - philo->data->start, id, str);
	pthread_mutex_unlock(&philo->data->speak);
	return (0);
}

void	write_data_dead(t_data *data)
{
	pthread_mutex_lock(&data->m_check);
	data->ph_dead = 1;
	pthread_mutex_unlock(&data->m_check);
}
