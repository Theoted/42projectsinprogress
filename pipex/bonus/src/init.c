/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:09:37 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/25 17:04:42 by tdeville         ###   ########lyon.fr   */
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
		write(STDERR_FILENO, "infile: Not found or permission denied\n", 39);
	data->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		write(STDERR_FILENO, "outfile: Permission denied\n", 28);
	return (0);
}

int	find_path_env(t_pipex *data, char **envp)
{
	data->path = find_path(envp);
	if (!data->path)
		return (error("PATH variable not found\n"));
	data->s_path = ft_split(data->path, ':');
	if (!data->s_path)
	{
		free(data->path);
		return (1);
	}
	free(data->path);
	return (0);
}

int	data_init(t_pipex *data, char **av, int ac, char **envp)
{
	data->nb_cmd = (ac - 3);
	if (check_hd(av, ac, data))
	{
		if (ac < 6)
			return (error("Bad args\n"));
		if (ft_here_doc(av, ac, data) == 1)
			return (1);
	}
	else if (open_files(data, av, ac) == 1)
		return (1);
	data->pid = malloc(sizeof(pid_t) * data->nb_cmd);
	data->fd = malloc(sizeof(int) * ((data->nb_cmd - 1) * 2));
	if (!data->fd || !data->pid)
	{
		if (data->pid)
			free(data->pid);
		close(data->infile);
		close(data->outfile);
		return (error("Malloc error\n"));
	}
	if (find_path_env(data, envp) == 1)
		return (1);
	open_pipes(data);
	return (0);
}
