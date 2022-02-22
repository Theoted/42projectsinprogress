/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:10:16 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/22 15:50:34 by tdeville         ###   ########lyon.fr   */
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
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	pid_t	*pid;
	int		*fd;
	char	*path;
	char	**s_path;
	char	*cmd;
	char	**arg;
	int		nb_cmd;
}			t_pipex;

// main
char		*find_cmd(char **arg_vec, t_pipex data);
char		*find_path(char **envp);

// Init
int			open_pipes(t_pipex *data);
int			open_files(t_pipex *data, char **av, int ac);
int			data_init(t_pipex *data, char **av, int ac, char **envp);
int			check_hd(char **av, int ac, t_pipex *data);

// Access
int			check_access(char **arg_vec, char **arg);

// Here_doc
int			ft_here_doc(char **av, int ac, t_pipex *data);

//utils
void		free_all(char **str);
int			error(char *err);
int			double_arrlen(char **str);
void		del(char *str);
void		last_free(t_pipex *data);
void		free_in_process(char **arg, t_pipex *data);
void		arg_error(char *err);

#endif
