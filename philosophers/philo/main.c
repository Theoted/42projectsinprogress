/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:41:53 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/11 10:47:16 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	struct timeval	start;
	struct timeval	end;
	t_philo			philo;

	philo = *(t_philo *)arg;
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	printf("%d %d as taken a fork\n", (start.tv_usec - start.tv_usec), philo.id);
	pthread_mutex_lock(&philo.fork);
	if (philo.id - 1 == -1)
		pthread_mutex_lock(&philo.data.philos[philo.data.ph_nb].fork);
	else
		pthread_mutex_lock(&philo.data.philos[philo.id - 1].fork);
	gettimeofday(&end, NULL);
	printf("%d %d is eating\n", (end.tv_usec - start.tv_usec), philo.id);
	while ((end.tv_usec - start.tv_usec) < philo.data.eat)
		gettimeofday(&end, NULL);
	printf("%d %d is sleeping\n", (end.tv_usec - start.tv_usec), philo.id);
	while ((end.tv_usec - start.tv_usec) < philo.data.sleep)
		gettimeofday(&end, NULL);
	printf("%d %d is thinking\n", (end.tv_usec - start.tv_usec), philo.id);
	pthread_mutex_unlock(&philo.fork);
	if (philo.id - 1 == -1)
		pthread_mutex_unlock(&philo.data.philos[philo.data.ph_nb].fork);
	else
		pthread_mutex_unlock(&philo.data.philos[philo.id - 1].fork);
	return (NULL);
}

t_data init_data(char **av)
{
	t_data	data;

	data.ph_nb = ft_atoi(av[1]);
	data.die = ft_atoi(av[2]);
	data.eat = ft_atoi(av[3]);
	data.sleep = ft_atoi(av[4]);
	return (data);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*ph;
	int			i;
	
	if (ac < 5)
		printf("Arg Error\n");
	data = init_data(av);
	ph = malloc(sizeof(t_philo) * data.ph_nb);
	data.philos = malloc(sizeof(t_philo) * data.ph_nb);
	i = -1;
	pthread_mutex_init(&data.speak, NULL);
	while (++i < data.ph_nb)
	{
		ph[i].id = i;
		pthread_mutex_init(&ph[i].fork, NULL);
		ph[i].eats = 0;
		ph[i].data = data;
		data.philos[i] = ph[i];
	}
	i = -1;
	while (++i < data.ph_nb)
		if (pthread_create(&ph[i].thread, NULL, &routine, &ph[i]) == -1)
			printf("Thread creting %d error\n", i);
	i = -1;
	while (++i < data.ph_nb)
		if (pthread_join(ph[i].thread, NULL) == -1)
			printf("Thread join %d error\n", i);
		
	return (0);
}
