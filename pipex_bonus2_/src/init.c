/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:09:37 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/23 09:56:45 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_pipes(t_pipex *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < (data->nb_cmd - 1))
	{	
		if (pipe(&data->fd[i * 2]) == -1)
		{
			while (++j < i)
				close(data->fd[j]);
			return (error("Pipe error\n"));
		}
	}
	return (0);
}

int	open_files(t_pipex *data, char **av, int ac)
{
	data->hd = 0;
	data->infile = open(av[1], O_RDONLY, 0644);
	if (data->infile == -1)
		return (error("infile not found\n"));
	data->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		close(data->infile);
		return (error("open error\n"));
	}
	return (0);
}

int	data_init(t_pipex *data, char **av, int ac, char **envp)
{
	data->nb_cmd = (ac - 3);
	if (check_hd(av, ac, data))
		ft_here_doc(av, ac, data);
	else if (open_files(data, av, ac) == 1)
		return (1);
	data->pid = malloc(sizeof(pid_t) * data->nb_cmd);
	if (!data->pid)
	{
		close(data->infile);
		close(data->outfile);
		return (error("Malloc error\n"));
	}
	data->fd = malloc(sizeof(int) * ((data->nb_cmd - 1) * 2));
	if (!data->fd)
	{
		close(data->infile);
		close(data->outfile);
		free(data->pid);
		return (error("Malloc error\n"));
	}
	data->path = find_path(envp);
	data->s_path = ft_split(data->path, ':');
	free(data->path);
	open_pipes(data);
	return (0);
}
