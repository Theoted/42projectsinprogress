/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 10:01:09 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/28 11:06:31 by tdeville         ###   ########lyon.fr   */
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

void	arg_error(char *err)
{
	if (err)
		write(STDERR_FILENO, err, ft_strlen(err));
	exit(1);
}
