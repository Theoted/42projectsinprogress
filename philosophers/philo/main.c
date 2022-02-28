/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:41:53 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/25 15:08:22 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

float   gtime(struct timeval *st, struct timeval *end)
{
    return (((end->tv_sec - st->tv_sec) + 1e-6
            * (end->tv_usec - st->tv_usec)) * 1000);
}

int	try_eat(t_philo *philo)
{
	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	
	// Take fork and lock speak
	pthread_mutex_lock(&philo->data->speak);
	pthread_mutex_lock(&philo->data->philos[philo->id].fork);
	printf("%d ph %d as taken a fork\n", (int)gtime(&start, &end), philo->id);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->data->philos[philo->data->ph_nb - 1].fork);
	else
		pthread_mutex_lock(&philo->data->philos[philo->id - 1].fork);
	// set time for eating
	philo->time_eat = gtime(&start, &end);
	
	// start eating
	while ((int)gtime(&start, &end) < philo->data->eat)
		gettimeofday(&end, NULL);
	printf("%d ph %d is eating\n", (int)gtime(&start, &end), philo->id);
	
	// Unlocking fork after eat
	pthread_mutex_unlock(&philo->data->philos[philo->id].fork);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->data->philos[philo->data->ph_nb - 1].fork);
	else
		pthread_mutex_unlock(&philo->data->philos[philo->id - 1].fork);
		
	// start sleeping
	while ((int)gtime(&start, &end) < philo->data->sleep)
		gettimeofday(&end, NULL);
	printf("%d ph %d is sleeping\n", (int)gtime(&start, &end), philo->id);
	
	pthread_mutex_unlock(&philo->data->speak);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			philo;

	philo = *(t_philo *)arg;
	if (philo.id % 2 == 0)
		try_eat(&philo);
	else
	{
		usleep(2000);
		try_eat(&philo);
	}
	
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
		ph[i].data = &data;
		ph[i].data->philos[i] = ph[i];
	}
	i = -1;
	while (++i < data.ph_nb)
		if (pthread_create(&ph[i].thread, NULL, &routine, &ph[i]) == -1)
			printf("Thread creating %d error\n", i);
	i = -1;
	while (++i < data.ph_nb)
		if (pthread_join(ph[i].thread, NULL) == -1)
			printf("Thread join %d error\n", i);
		
	return (0);
}
