/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:03:49 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/28 17:12:59 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_hd(t_pipex data, char **envp, int i)
{
	data.pid[i] = fork();
	if (!data.pid[i])
	{
		if (i == data.nb_cmd - 1)
		{
			if (dup2(data.outfile, STDOUT_FILENO) == -1
				|| dup2(data.fd[2], STDIN_FILENO) == -1)
				exit(1);
		}
		else
		{
			if (dup2(data.fd[0], STDIN_FILENO) == -1
				|| dup2(data.fd[3], STDOUT_FILENO) == -1)
				exit(1);
		}
		close_all(&data);
		if (execve(data.cmd, data.arg, envp) == -1)
			exit(1);
	}
}

int	ft_here_doc(char **av, int ac, t_pipex *data)
{
	char	*buffer;
	int		longest;

	while (1)
	{
		write(STDOUT_FILENO, "pipe heredoc> ", 15);
		buffer = get_next_line(STDIN_FILENO);
		longest = ft_strlen(av[2]);
		if (ft_strlen(buffer) > ft_strlen(av[2]))
			longest = ft_strlen(buffer) - 1;
		if (!av[2][0] && buffer[0] == '\n')
			break ;
		if (!ft_strncmp(buffer, av[2], longest))
			break ;
		write(data->fd[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	data->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data->outfile == -1)
		write(STDERR_FILENO, "outfile permission denied\n", 27);
	return (0);
}

int	check_hd(char **av, int ac, t_pipex *data)
{
	int	i;

	i = 0;
	(void)ac;
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		data->hd = 1;
		data->nb_cmd = 2;
		data->pid = malloc(sizeof(pid_t) * (data->nb_cmd));
		data->fd = malloc(sizeof(int) * (data->nb_cmd * 2));
		open_pipes(data);
		return (1);
	}
	return (0);
}
