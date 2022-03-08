/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:51:37 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/08 13:23:15 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_die(t_data *data, int i)
{
	pthread_mutex_lock(&data->m_gettime);
	if (data->philos[i].running
		&& (timems() - data->philos[i].time_eat) >= data->die)
	{
		write_data_dead(data);
		pthread_mutex_lock(&data->speak);
		printf("%lld %d died\n", (timems() - data->start), i + 1);
		pthread_mutex_unlock(&data->speak);
		pthread_mutex_unlock(&data->m_gettime);
		return (1);
	}
	pthread_mutex_unlock(&data->m_gettime);
	return (0);
}
