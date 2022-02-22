/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 10:55:35 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/22 10:32:04 by tdeville         ###   ########lyon.fr   */
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

char	*find_cmd(char **arg_vec, t_pipex data)
{
	int		i;
	char	*arg;
	char	*tmp;

	i = -1;
	arg = NULL;
	if (check_access(arg_vec, &arg) == 2)
		return (ft_strdup(arg_vec[0]));
	tmp = arg_vec[0];
	arg_vec[0] = ft_strjoin("/", arg_vec[0]);
	free(tmp);
	while (data.s_path[++i])
	{
		arg = ft_strjoin(data.s_path[i], arg_vec[0]);
		if (check_access(arg_vec, &arg) == 0)
			return (ft_strjoin(data.s_path[i], arg_vec[0]));
		else if (check_access(arg_vec, &arg) == 1)
			error("Permission denied\n");
		free(arg);
	}
	error(ft_strjoin(&arg_vec[0][1], " : command not found\n"));
	return (0);
}

void	close_all(t_pipex *data)
{
	int	i;

	i = -1;
	while (++i < (data->nb_cmd - 1) * 2)
		close(data->fd[i]);
	close(data->infile);
	close(data->outfile);
}

void	exec(t_pipex data, char **envp, int i)
{
	data.pid[i] = fork();
	if (!data.pid[i])
	{
		if (i == 0)
		{
			dup2(data.infile, STDIN_FILENO);
			dup2(data.fd[(i * 2) + 1], STDOUT_FILENO);
		}
		else if (i == data.nb_cmd - 1)
		{
			dup2(data.outfile, STDOUT_FILENO);
			dup2(data.fd[(i - 1) * 2], STDIN_FILENO);
		}
		else
		{
			dup2(data.fd[(i - 1) * 2], STDIN_FILENO);
			dup2(data.fd[(i * 2) + 1], STDOUT_FILENO);
		}
		close_all(&data);
		if (execve(data.cmd, data.arg, envp) == -1)
			exit(1);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_pipex	data;
	char	**arg;

	if (ac < 5)
		arg_error("bad arguments\n");
	if (data_init(&data, av, ac, envp) == 1)
		return (1);
	i = -1;
	while (++i < data.nb_cmd)
	{
		arg = ft_split(av[i + 2], ' ');
		data.cmd = find_cmd((arg), data);
		data.arg = ft_split(av[i + 2], ' ');
		exec(data, envp, i);
		free_in_process(arg, &data);
	}
	close_all(&data);
	i = -1;
	while (++i < data.nb_cmd)
		waitpid(data.pid[i], NULL, 0);
	last_free(&data);
	return (0);
}