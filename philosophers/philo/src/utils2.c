/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:51:37 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/09 14:20:55 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_die(t_data *data, int i)
{
	long long int	time;

	pthread_mutex_lock(&data->speak);
	time = timems();
	pthread_mutex_lock(&data->m_gettime);
	if (data->philos[i].running
		&& (time - data->philos[i].time_eat) >= data->die)
	{
		write_data_dead(data);
		printf("%lld %d died\n", (time - data->start), i + 1);
		pthread_mutex_unlock(&data->speak);
		pthread_mutex_unlock(&data->m_gettime);
		return (1);
	}
	pthread_mutex_unlock(&data->m_gettime);
	pthread_mutex_unlock(&data->speak);
	return (0);
}

int	check_args(int ac, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
	}
	return (0);
}

int	check_data(t_data data)
{
	if ((data.eat < 60) || (data.die < 60) || (data.sleep < 60))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	return_error(char *str)
{
	printf("%s\n", str);
	return (1);
}
