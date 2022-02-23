/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:59:20 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/23 11:03:49 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	check_access(char **arg_vec, char **arg)
{
	if (!access(arg_vec[0], F_OK))
	{
		if (!access(arg_vec[0], R_OK))
			return (2);
	}
	else if (!access(*arg, F_OK))
	{
		if (!access(*arg, R_OK))
		{
			free(*arg);
			return (0);
		}	
		else
		{
			free(*arg);
			return (1);
		}
	}
	return (4);
}
