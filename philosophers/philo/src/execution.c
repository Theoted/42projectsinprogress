/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:52:18 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/03 13:52:31 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_die(t_philo *philo)
{
	if ((timems() - philo->time_eat) >= philo->data->die)
	{
		philo->died = 1;
		printf("%lld philo %d died\n", (timems() - philo->time_eat), philo->id);
		return (1);
	}
	return (0);
}
