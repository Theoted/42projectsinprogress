/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:02:56 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/09 13:09:32 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_all(t_data *data, char *str, int x)
{
	int	i;

	i = -1;
	if (str)
		printf("%s\n", str);
	if (x == 1)
		while (++i < data->ph_nb)
			pthread_mutex_destroy(&data->philos[i].fork);
	pthread_mutex_destroy(&data->speak);
	pthread_mutex_destroy(&data->m_check);
	pthread_mutex_destroy(&data->m_gettime);
	free(data->philos);
	return (1);
}
