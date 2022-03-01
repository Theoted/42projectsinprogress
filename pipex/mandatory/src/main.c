/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 10:55:35 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/01 10:48:40 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->outfile);
	close(pipex->infile);
}

int	data_init(t_pipex *pipex, char **envp, char **av)
{
	pipex->infile = open(av[1], O_RDONLY, 0644);
	if (pipex->infile == -1)
		error(av[1]);
	pipex->outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		error(av[4]);
	pipex->path = find_path(envp);
	if (!pipex->path)
		return (error("PATH variable not found\n"));
	pipex->s_path = ft_split(pipex->path, ':');
	if (!pipex->s_path)
	{
		free(pipex->path);
		return (1);
	}
	return (0);
}

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

char	*find_cmd(char **arg_vec, t_pipex pipex)
{
	int		i;
	char	*arg;
	char	*tmp;

	i = -1;
	arg = 0;
	if (check_access(arg_vec, &arg) == 2)
		return (ft_strdup(arg_vec[0]));
	tmp = arg_vec[0];
	arg_vec[0] = ft_strjoin("/", arg_vec[0]);
	free(tmp);
	while (pipex.s_path[++i])
	{
		arg = ft_strjoin(pipex.s_path[i], arg_vec[0]);
		if (!arg)
			exit(1);
		if (check_access(arg_vec, &arg) == 0)
			return (ft_strjoin(pipex.s_path[i], arg_vec[0]));
		else if (check_access(arg_vec, &arg) == 1)
			error("Permission denied\n");
		free(arg);
	}
	arg_error(": command not found\n", &arg_vec[0][1]);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	pid_t	pid;
	pid_t	pid1;

	if (ac != 5)
		return (arg_error("Bad arguments\n", NULL));
	if (pipe(pipex.fd) == -1)
		return (error("Pipe error\n"));
	if (data_init(&pipex, envp, av) == 1)
		return (1);
	pid = fork();
	if (pid == 0)
		fork_child(pipex, av, envp);
	pid1 = fork();
	if (pid1 == 0)
		fork_parent(pipex, av, envp);
	close_pipes(&pipex);
	waitpid(pid, NULL, 0);
	waitpid(pid1, NULL, 0);
	free(pipex.path);
	free_all(pipex.s_path);
	return (0);
}
