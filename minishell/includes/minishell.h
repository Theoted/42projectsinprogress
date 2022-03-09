/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:24:25 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/09 18:45:31 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_args t_args;
typedef struct s_data_p t_data_p;

struct s_args
{
	char    **env_path;
	char    *path;
	char	*stdin_arg;
};

struct s_data_p
{
	int	exit;	
	int	check_squotes;
	int	check_dquotes;
};

/* ------------------- PARSING ------------------- */
	// Bin Path
int		find_env_path(char **envp, t_args *args);
int		ft_access(char *arg);
int		check_pipe(char *line);
int		pipe_not_in_quotes(char *line);

	// Parsing Utils
int		ft_isquotes(char c);

	// Split Pipes
int		count_pipes(char const *s, t_data_p data);

#endif