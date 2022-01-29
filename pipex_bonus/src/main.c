/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 10:55:35 by tdeville          #+#    #+#             */
/*   Updated: 2022/01/29 15:19:38 by tdeville         ###   ########lyon.fr   */
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

char	*find_cmd(char **arg_vec, char **envp, t_pipex *data)
{
	int		i;
	char	*arg;
	char	*join;

	i = -1;
	data->path = find_path(envp);
	data->s_path = ft_split(data->path, ':');
	free(data->path);
	arg = ft_strjoin("/", arg_vec[0]);
	while (data->s_path[++i])
	{
		join = ft_strjoin(data->s_path[i], arg);
		if (!access(join, F_OK))
		{
			if (!access(join, R_OK))
			{
				free(arg);
				free_all(data->s_path);
				return (join);
			}
			else
				data->check = 1;
		}
		free(join);
	}
	free(arg);
	free_all(data->s_path);
	error(ft_strjoin(&arg_vec[0][0], " : command not found\n"), data->check, *data);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	// t_pipex	pipex;
	// int		pid;
	// int		pid1;
	// int		*pidd;
	// int		i;

	// i = 0;
	// // if (ac != 5)
	// // {
	// // 	error("Bad arguments\n");
	// // 	return (1);
	// // }
	// pipex.fd = malloc(sizeof(int) * (ac - 3) * 2);
	// pidd = malloc(sizeof(int) * (ac - 3));
	// if (pipe(pipex.fd) == -1)
	// 	exit(1);
	// pid = fork();
	// if (pid == 0)
	// 	fork_child(pipex, av, envp);
	// pid1 = fork();
	// if (pid1 == 0)
	// 	fork_parent(pipex, av, envp);
	// // (void)ac;
	// // (void)av;
	// // (void)envp;

	////////////////////////
	int		i;
	char	**args;
	t_cmds	*cmds;
	t_pipex	data;
	
	i = -1;
	cmds = NULL;
	data.pid = malloc(sizeof(int) * (ac - 3));
	data.fd = malloc(sizeof(int *) * (ac - 3));
	while (++i < (ac - 3))
		data.fd[i] = malloc(sizeof(int) * 2);
	i = 0;
	while (i < (ac - 3))
	{
		args = ft_split(av[i + 2], ' ');
		ft_lstadd_back1(&cmds, ft_lstnew_double(find_cmd(args, envp, &data), args));
		free_all(args);
		i++;
	}
	i = 0;
	while (cmds)
	{
		pipe(data.fd[i]);
		close(data.fd[i][0]);
		data.pid[i] = fork();
		if (!data.pid[i] && ((i + 1) != (ac - 3)))
		{
			data.file1 = open(av[1], O_RDONLY, 0644);
			dup2(data.file1, STDIN_FILENO);
			dup2(data.fd[i][1], STDOUT_FILENO);
			close(data.file1);
			execve(cmds->cmd, cmds->arg_vec_t, envp);
			return (0);
		}
		if (!data.pid[i] && (i + 1) == (ac - 3))
		{
			data.file2 = open(av[ac - 1], O_RDWR | O_CREAT, 0644);
			dup2(data.file2, STDOUT_FILENO);
			dup2(data.fd[i][0], STDIN_FILENO);
			close(data.file2);
			execve(cmds->cmd, cmds->arg_vec_t, envp);
			return (0);
		}
		waitpid(data.pid[i], NULL, 0);
		cmds = cmds->next;
		i++;
	}
	// ft_lstclear1(&cmds, (void *)del);
	return (0);
}
