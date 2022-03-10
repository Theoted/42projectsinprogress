/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:24:25 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/10 17:50:39 by tdeville         ###   ########lyon.fr   */
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
typedef struct s_lexer t_lexer;
typedef struct s_cmds t_cmds;

struct s_args
{
	char    **env_path;
	char    *path;
	char	*stdin_arg;
	char	**args_vec;
};

struct s_data_p
{
	int		pipes_nb;
	int		args_create;
	char	**args;
};

struct s_cmds
{
	char 			*arg;
	struct s_cmds	*next;
}; 

struct s_lexer
{
	int	squotes;
	int	dquotes;
	int	dollar;
	int	l_pipe;
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
// char 	**lexer_pipes(char const *s, t_data_p data);
// char	**ft_split_p(char const *s, t_data_p data);
// int		count_pipes(char const *s, t_data_p data);
// int		pipe_ok(char const *s, size_t len, t_data_p data);
// int		pipe_before_quote(char const *s, int i);

	// Lexer
int		lexer(char *arg, t_data_p *data);
int		squote_check(char *arg, int i, t_data_p *data);
int		pipe_check(char *arg, int i);
int		synthax_checker(char *arg);
void	create_arg(char *str, int i, t_data_p *data, int bad_pipe);
int		count_pipes(char *str);
int		pipe_synthax(char *str, t_data_p data);

#endif