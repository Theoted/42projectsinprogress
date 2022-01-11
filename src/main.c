/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 10:55:35 by tdeville          #+#    #+#             */
/*   Updated: 2022/01/11 10:18:51 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*find_cmd(char **arg_vec, char **envp, t_pipex pipex)
{
	int		i;

	i = -1;
	pipex.path = find_path(envp);
	pipex.s_path = ft_split(pipex.path, ':');
	free(pipex.path);
	arg_vec[0] = ft_strjoin("/", arg_vec[0]);
	while (pipex.s_path[++i])
	{
		if (!access(ft_strjoin(pipex.s_path[i], arg_vec[0]), F_OK))
		{
			if (!access(ft_strjoin(pipex.s_path[i], arg_vec[0]), R_OK))
				return (ft_strjoin(pipex.s_path[i], arg_vec[0]));
			else
				error("Permission denied\n");
		}
	}
	error(ft_strjoin(&arg_vec[0][1], " : command not found\n"));
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		pid;
	int		pid1;

	if (ac != 5)
	{
		error("Bad arguments\n");
		return (1);
	}
	if (pipe(pipex.fd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		fork_child(pipex, av, envp);
	pid1 = fork();
	if (pid1 == 0)
		fork_parent(pipex, av, envp);
	return (0);
}
