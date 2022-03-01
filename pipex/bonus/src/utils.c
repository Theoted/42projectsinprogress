/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 10:01:09 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/01 10:41:20 by tdeville         ###   ########lyon.fr   */
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
	errno = 0;
	return (1);
}

void	free_in_process(char **arg, t_pipex *data)
{
	free_all(arg);
	free_all(data->arg);
	free(data->cmd);
}

void	last_free(t_pipex *data)
{
	free_all(data->s_path);
	free(data->fd);
	free(data->pid);
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
