/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:42:35 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/07 16:09:00 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	init_data(char **av)
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
	data.ready = 0;
	pthread_mutex_init(&data.speak, NULL);
	data.philos = malloc(sizeof(t_philo) * data.ph_nb);
	return (data);
}

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_nb)
	{
		data->philos[i].id = i;
		pthread_mutex_init(&data->philos[i].fork, NULL);
		data->philos[i].eats = 0;
		data->philos[i].data = data;
		data->philos[i].died = 0;
		data->philos[i].running = 1;
		data->philos[i].time_eat = timems();
	}
}
