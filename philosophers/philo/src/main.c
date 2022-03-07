/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:41:53 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/07 16:19:30 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	timems(void)
{
	struct timeval	start;
	long long int	time;

	gettimeofday(&start, NULL);
	time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (time);
}

int	check_die_and_eat(t_data *data)
{
	int	i;
	long long int time;

	i = -1;
	while (++i < data->ph_nb)
	{
		pthread_mutex_lock(&data->speak);
		if (data->eats_done == data->ph_nb)
		{
			pthread_mutex_unlock(&data->speak);
			return (1);
		}
		pthread_mutex_unlock(&data->speak);
		time = timems();
		pthread_mutex_lock(&data->speak);
		if (data->philos[i].running
			&& (time - data->philos[i].time_eat) >= data->die)
		{
			data->ph_dead = 1;
			printf("%lld %d died\n",
				(time - data->philos[i].time_eat), i + 1);
			pthread_mutex_unlock(&data->speak);
			return (1);
		}
		pthread_mutex_unlock(&data->speak);
		if (i == data->ph_nb - 1)
			i = -1;
	}
	return (0);
}

int	try_eat(t_philo *philo)
{
	if (philo->data->ph_nb == 1)
		return (one_philo_eating(philo));
	while (1)
	{
		if (fork_and_eat(philo) == 1)
			break ;
		pthread_mutex_lock(&philo->data->speak);
		philo->data->philos[philo->id].time_eat = timems();
		pthread_mutex_unlock(&philo->data->speak);
		ft_mutex_unlock(philo);
		if (sleeping(philo) == 1)
			break ;
		if (thinking(philo) == 1)
			break ;
		philo->eats++;
		if (check_eats(philo))
			break ;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->speak);
		if (philo->data->ready == 1)
		{
			pthread_mutex_unlock(&philo->data->speak);
			break ;
		}
		pthread_mutex_unlock(&philo->data->speak);
	}
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->eat, philo);
	try_eat(philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i;

	if (ac != 5 && ac != 6)
	{
		printf("Arg Error\n");
		return (0);
	}
	data = init_data(av);
	init_philo(&data);
	i = -1;
	while (++i < data.ph_nb)
		if (pthread_create(&data.philos[i].thread, NULL,
				&routine, &data.philos[i]) == -1)
			printf("Thread creating %d error\n", i);
	data.start = timems();
	data.ready = 1;
	if (check_die_and_eat(&data) == 1)
	{
		i = -1;
		while (++i < data.ph_nb)
			if (pthread_join(data.philos[i].thread, NULL) == -1)
				printf("Thread join %d error\n", i);
	}
	free(data.philos);
	return (0);
}
