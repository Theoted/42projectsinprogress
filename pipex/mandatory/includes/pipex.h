/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:10:16 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/23 10:28:58 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include "../../libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		fd[2];
	char	**arg_vec;
	char	*cmd;
	char	*path;
	char	**s_path;
}		t_pipex;

// main
char	*find_cmd(char **arg_vec, t_pipex pipex);
char	*find_path(char **envp);

// execution
void	fork_child(t_pipex pipex, char **av, char **envp);
void	fork_parent(t_pipex pipex, char **av, char **envp);

//utils
void	free_all(char **str);
int		error(char *err);

#endif
