/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:41:53 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/02 14:24:40 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

float   gtime(struct timeval *st, struct timeval *end)
{
    return (((end->tv_sec - st->tv_sec) + 1e-6
            * (end->tv_usec - st->tv_usec)) * 1000);
}

int	check_die(t_philo *philo)
{
	struct timeval end;
	gettimeofday(&end, NULL);

	if (philo->eats == 0)
	{
		printf("time between eat and now: %d, philo: %d\n", (int)gtime(&philo->data->start, &end), philo->id);
		if ((int)gtime(&philo->data->start, &end) > philo->data->die)
		{
			printf("DIED\n");	
			return (1);
		}
	}
	else
	{
		printf("time between eat and now: %d, philo: %d\n", (int)gtime(&philo->time_eat, &end), philo->id);
		if ((int)gtime(&philo->time_eat, &end) > philo->data->die)
		{
			printf("DIED\n");		
			return (1);
		}
		
	}
	return (0);
}

int	try_eat(t_philo *philo)
{
	struct timeval	end;
	struct timeval	start;
	int				loop_time;
	
	loop_time = 0;
	while (++loop_time < 20)
	{
		// Take fork and lock speak
		// pthread_mutex_lock(&philo->data->speak);
		gettimeofday(&start, NULL);
		// philo->time_eat = start;
		pthread_mutex_lock(&philo->data->philos[philo->id].fork);
		gettimeofday(&start, NULL);
		gettimeofday(&end, NULL);
		check_die(philo);
		printf("%d ph %d as taken a fork\n", (int)gtime(&philo->data->start, &end), philo->id);
		if (philo->id == 0)
			pthread_mutex_lock(&philo->data->philos[philo->data->ph_nb - 1].fork);
		else
			pthread_mutex_lock(&philo->data->philos[philo->id - 1].fork);
		// set time for eating
		// start eating
		printf("%d ph %d is eating\n", (int)gtime(&philo->data->start, &end), philo->id);
		while ((int)gtime(&start, &end) < (philo->data->eat))
			gettimeofday(&end, NULL);
		
		
		// Unlocking fork after eat
		pthread_mutex_unlock(&philo->data->philos[philo->id].fork);
		if (philo->id == 0)
			pthread_mutex_unlock(&philo->data->philos[philo->data->ph_nb - 1].fork);
		else
			pthread_mutex_unlock(&philo->data->philos[philo->id - 1].fork);
		
		
		// start sleeping
		gettimeofday(&start, NULL);
		gettimeofday(&end, NULL);
		printf("%d ph %d is sleeping\n", (int)gtime(&philo->data->start, &end), philo->id);
		while ((int)gtime(&start, &end) < (philo->data->sleep))
			gettimeofday(&end, NULL);
		// pthread_mutex_unlock(&philo->data->speak);
		philo->eats++;
	}
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
		usleep(1000 * philo.data->eat);
		try_eat(&philo);
	}
	
	return (NULL);
}

t_data init_data(char **av)
{
	t_data	data;

	gettimeofday(&data.start, NULL);
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
