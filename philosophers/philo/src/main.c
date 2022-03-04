/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:41:53 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/04 11:29:46 by tdeville         ###   ########lyon.fr   */
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

	i = -1;
	while (++i < data->ph_nb)
	{
		if (data->eats_done == data->ph_nb)
		{
			
			return (1);
		}
		pthread_mutex_lock(&data->speak);
		if (data->philos[i].running && (timems() - data->philos[i].time_eat) >= data->die)
		{
			data->ph_dead = 1;
			printf("%lld philo %d died\n", (timems() - data->philos[i].time_eat), i);
			return (1);
		}
		pthread_mutex_unlock(&data->speak);
		if (i == data->ph_nb - 1)
			i = -1;
		usleep(100);
	}
	return (0);
}

int	try_eat(t_philo *philo)
{
	while (1 && philo->data->ph_dead == 0)
	{
		ft_mutex_lock(philo);
		if (philo->data->ph_dead == 1 || philo->data->check_eat == 1)
			break ;
		printf("%lld ph %d is eating\n", (timems() - philo->data->start), philo->id);
		ft_usleep(philo->data->eat);
		philo->data->philos[philo->id].time_eat = timems();
		ft_mutex_unlock(philo);
		if (philo->data->ph_dead == 1 || philo->data->check_eat == 1)
			break ;
		sleeping(philo);
		if (philo->data->ph_dead == 1 || philo->data->check_eat == 1)
			break ;
		thinking(philo);
		philo->eats++;
		if (check_eats(philo))
			break ;
		usleep(100);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		try_eat(philo);
	else
	{
		ft_usleep(philo->data->eat);
		try_eat(philo);
	}
	return (NULL);
}

t_data init_data(char **av)
{
	t_data	data;
	
	if (av[5])
		data.eat_nb = ft_atoi(av[5]);
	data.check_eat = 0;
	data.ph_nb = ft_atoi(av[1]);
	data.die = ft_atoi(av[2]);
	data.eat = ft_atoi(av[3]);
	data.sleep = ft_atoi(av[4]);
	data.eats_done = 0;
	data.ph_dead = 0;
	data.start = timems();
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
		ph[i].died = 0;
		ph[i].running = 1;
		ph[i].time_eat = timems();
		ph[i].data->philos[i] = ph[i];
	}
	i = -1;
	while (++i < data.ph_nb)
		if (pthread_create(&ph[i].thread, NULL, &routine, &ph[i]) == -1)
			printf("Thread creating %d error\n", i);
	if (check_die_and_eat(&data) == 1)
	{
		i = -1;
		while (++i < data.ph_nb)
			if (pthread_join(ph[i].thread, NULL) == -1)
				printf("Thread join %d error\n", i);
	}
	return (0);
}
