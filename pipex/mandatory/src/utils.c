/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 10:01:09 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/01 10:51:30 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	error(char *err)
{
	if (err)
		perror(err);
	return (1);
}

int	check_access(char **arg_vec, char **arg)
{
	if (!access(arg_vec[0], X_OK))
	{
		if (!access(arg_vec[0], R_OK))
			return (2);
	}
	else if (!access(*arg, X_OK))
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

int	arg_error(char *err, char *cmd)
{
	if (err)
	{
		if (cmd)
			write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, err, ft_strlen(err));
	}
	return (1);
}
