/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 09:39:57 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/01 10:50:18 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fork_child(t_pipex pipex, char **av, char **envp)
{
	close(pipex.fd[0]);
	pipex.arg_vec = ft_split(av[2], ' ');
	if (!pipex.arg_vec)
		exit(4);
	pipex.cmd = find_cmd(pipex.arg_vec, pipex);
	if (!pipex.cmd)
		exit(4);
	if (dup2(pipex.infile, STDIN_FILENO) == -1)
		exit(2);
	if (dup2(pipex.fd[1], STDOUT_FILENO) == -1)
		exit(2);
	if (close(pipex.fd[1]) == -1)
		exit(1);
	if (close(pipex.infile) == -1)
		exit(1);
	if (execve(pipex.cmd, pipex.arg_vec, envp) == -1)
		exit(3);
}

void	fork_parent(t_pipex pipex, char **av, char **envp)
{
	close(pipex.fd[1]);
	pipex.arg_vec = ft_split(av[3], ' ');
	if (!pipex.arg_vec)
		exit(4);
	pipex.cmd = find_cmd(pipex.arg_vec, pipex);
	if (!pipex.cmd)
		exit(4);
	if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		exit(2);
	if (dup2(pipex.fd[0], STDIN_FILENO) == -1)
		exit(2);
	if (close(pipex.fd[0]) == -1)
		exit(1);
	if (close(pipex.outfile) == -1)
		exit(1);
	if (execve(pipex.cmd, pipex.arg_vec, envp) == -1)
		exit(3);
}
