/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 09:39:57 by tdeville          #+#    #+#             */
/*   Updated: 2022/01/29 14:06:23 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// int	fork_child(t_pipex pipex, char **av, char **envp)
// {
// 	close(pipex.fd[0]);
// 	pipex.arg_vec = ft_split(av[2], ' ');
// 	pipex.cmd = find_cmd(pipex.arg_vec, envp, pipex);
// 	pipex.file1 = open(av[1], O_RDONLY, 0644);
// 	if (pipex.file1 == -1)
// 		error("infile not found\n");
// 	if (dup2(pipex.file1, STDIN_FILENO) == -1)
// 		exit(2);
// 	if (dup2(pipex.fd[1], STDOUT_FILENO) == -1)
// 		exit(2);
// 	if (close(pipex.fd[1]) == -1)
// 		exit(1);
// 	if (close(pipex.file1) == -1)
// 		exit(1);
// 	if (execve(pipex.cmd, pipex.arg_vec, envp) == -1)
// 		exit(3);
// 	free_all(pipex.arg_vec);
// 	free(pipex.cmd);
// 	free_all(pipex.s_path);
// }

// int	fork_parent(t_pipex pipex, char **av, char **envp)
// {
// 	wait(NULL);
// 	close(pipex.fd[1]);
// 	pipex.arg_vec = ft_split(av[3], ' ');
// 	pipex.cmd = find_cmd(pipex.arg_vec, envp, pipex);
// 	pipex.file2 = open(av[4], O_RDWR | O_CREAT, 0644);
// 	if (pipex.file2 == -1)
// 		exit(2);
// 	if (dup2(pipex.file2, STDOUT_FILENO) == -1)
// 		exit(2);
// 	if (dup2(pipex.fd[0], STDIN_FILENO) == -1)
// 		exit(2);
// 	if (close(pipex.fd[0]) == -1)
// 		exit(1);
// 	if (close(pipex.file2) == -1)
// 		exit(1);
// 	if (execve(pipex.cmd, pipex.arg_vec, envp) == -1)
// 		exit(3);
// 	free_all(pipex.arg_vec);
// 	free(pipex.cmd);
// 	free_all(pipex.s_path);
// }
