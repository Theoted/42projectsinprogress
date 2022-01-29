/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:10:16 by tdeville          #+#    #+#             */
/*   Updated: 2022/01/29 14:06:34 by tdeville         ###   ########lyon.fr   */
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

typedef	struct s_cmds
{
	char			*cmd;
	char			**arg_vec_t;
	struct s_cmds	*next;
}					t_cmds;


typedef struct s_pipex
{
	int		file1;
	int		file2;
	int		check;
	int		*pid;
	int		**fd;
	char	*path;
	char	**s_path;
	t_cmds	cmds;
}			t_pipex;

// main
char		*find_cmd(char **arg_vec, char **envp, t_pipex *pipex);
char		*find_path(char **envp);

// execution
int			fork_child(t_pipex pipex, char **av, char **envp);
int			fork_parent(t_pipex pipex, char **av, char **envp);

//utils
void		free_all(char **str);
void		error(char *err, int n, t_pipex data);
int			double_arrlen(char **str);
void		del(char *str);

// rebuild libft lst functions
t_cmds		*ft_lstnew_double(char *cmd, char **arg_vec);
void		ft_lstadd_back1(t_cmds **alst, t_cmds *new);
t_cmds		*ft_lstlast1(t_cmds *lst);
int			ft_lstsize1(t_cmds *lst);
void		ft_lstadd_front1(t_cmds **alst, t_cmds *new);
void		ft_lstdelone1(t_cmds *lst, void (*del)(void *));
void		ft_lstclear1(t_cmds **lst, void (*del)(void *));


#endif
