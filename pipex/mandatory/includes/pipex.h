/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:10:16 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/28 11:01:01 by tdeville         ###   ########lyon.fr   */
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
# include <errno.h>

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

// Functions
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);

#endif
