/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:01:31 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/04 11:13:53 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(int time)
{
	long long int start;
	long long int end;
	
	start = timems();
	end = timems();
	while (end - start < time)
	{
		usleep(100);
		end = timems();
	}
}
