/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:00:07 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/28 17:22:38 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_args(t_pipex *data, char **av, int i, char **arg)
{
	arg = ft_split(av[i + 2 + data->hd], ' ');
	if (!arg)
		exit(1);
	data->cmd = find_cmd((arg), *data);
	if (!data->cmd)
		exit(1);
	data->arg = ft_split(av[i + 2 + data->hd], ' ');
	if (!data->arg)
		exit(1);
	return (arg);
}
