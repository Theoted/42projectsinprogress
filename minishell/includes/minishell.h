/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:24:25 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/11 15:21:36 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_commands t_commands;
typedef struct s_data_p t_data_p;
typedef struct s_lexer t_lexer;

struct s_commands
{
	char	**args_vec;
	char	*cmd_path;
	char	*here_doc;
	char	*here_doc_del;
	int		infile;
	int		outfile;
	int		infile_type;
};

struct s_data_p
{
	char		*stdin_arg;
	char    	*path;
	char    	**env_path;
	char		**args;
	int			pipes_nb;
	int			args_create;
	t_commands	*commands;
};

/* ------------------- PARSING ------------------- */
	// Bin Path
int		find_env_path(char **envp, t_data_p *data);
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
int		pipe_check(char *arg, int i);
int		synthax_checker(char *arg);
int		split_args(char *arg, t_data_p *data);
int		create_arg(char *str, int i, t_data_p *data, int bad_pipe);
int		count_pipes(char *str);
int		pipe_synthax(char *str, t_data_p data);

	// Here_doc
int		check_heredoc(char *arg, t_data_p *data, int idx);
int		get_heredoc_del(char *arg, int i, t_data_p *data, int idx);
int		ft_here_doc(t_data_p *data, int idx);
int		here_doc_write(t_data_p *data, char *buffer, int idx);

#endif