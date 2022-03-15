/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:04:51 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/15 18:01:01 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	format_del(char *del, t_data_p *data, int idx)
{
	int		i;
	int		j;
	char	quote;
	char	*new_del;
	char	*tmp;
	
	i = -1;
	j = 0;
	quote = 0;
	new_del = ft_calloc(sizeof(char), (ft_strlen(del) + 1));
	while (del[++i])
	{
		if ((del[i] == '\'' || del[i] == '\"') && quote == 0)
			quote = del[i++];
		while (del[i] != quote && del[i] && quote != 0)
		{
			new_del[j++] = del[i++];
			if (del[i] == quote && quote != 0)
			{
				quote = 0;
				break ;
			}
		}
	}
	tmp = data->commands[idx].here_doc_del;
	data->commands[idx].here_doc_del = ft_strdup(new_del);
	free(tmp);
	return (0);
}

int	check_heredoc(char *arg, t_data_p *data, int idx)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '<' && arg[i + 1] == '<')
		{
			get_heredoc_del(arg, i + 2, data, idx);
			ft_here_doc(data, idx);
		}
		i++;
	}
	return (0);
}

int	get_heredoc_del(char *arg, int i, t_data_p *data, int idx)
{
	int		j;
	int		quote;

	quote = 0;
	data->commands[idx].expend_var = 1;
	while (arg[i] == ' ' && arg[i])
		i++;
	j = i;
	while (arg[i] != ' ' && arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
		{
			data->commands[idx].expend_var = 0;
			quote = 1;
		}
		i++;
	}
	data->commands[idx].here_doc_del = ft_substr(arg, j, i);
	if (quote != 0)
		format_del(data->commands[idx].here_doc_del, data, idx);
	return (0);
}

int	nb_of_env_vars(char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	fill_vars_tab(char **var, char *buffer, int *idx, int *k)
{
	int	j;
	int	check;

	j = *idx;
	check = 0;
	while (buffer[*idx] != ' ' && buffer[*idx])
	{
		if (buffer[*idx] == '\n')
			break ;
		(*idx)++;
		if (buffer[*idx] == '$')
		{
			check = 1;
			break ;
		}
	}
	*var = ft_substr(buffer, j + 1, (*idx - j) - 1);
	(*k)++;
	if (check == 1)
		(*idx)--;
}

int	get_expend_var(t_data_p *data, char *buffer)
{
	int		i;
	int		k;
	char	*tmp;
	char	**vars;

	i = -1;
	k = 0;
	vars = malloc(sizeof(char *) * (nb_of_env_vars(buffer) + 1));
	while (buffer[++i])
		if (buffer[i] == '$')
			fill_vars_tab(&vars[k], buffer, &i, &k);
	vars[k] = 0;
	i = 0;
	if (vars)
	{
		while (vars[i])
		{
			tmp = vars[i];
			vars[i] = expend_env_var(data->env_vars, vars[i]);
			if (!ft_strncmp(vars[i], tmp, ft_strlen(vars[i])))
				vars[i] = ft_strjoin("$", tmp);	
			free(tmp);
			i++;
		}
	}
	// expend_var_in_buffer(buffer, vars);
	return (0);
}

/*	L'objectif actuel est de reussir a expend les variables d'environnement
	dans le buffer et donc de modifier le buffer

	Je dois aussi checker si la variable existe ou non car si elle n'existe pas,
	elle est remplacée par une chaine vide. Cependant si elle n'existe pas mais
	qu'elle contient des quotes, elle sera affichée tel quel.
 */
// char	*expend_var_in_buffer(char *buffer, char **expended_vars)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**split_buffer;
// 	(void)expended_vars;

// 	i = -1;
// 	k = 0;
// 	split_buffer = malloc(sizeof(char *) * (nb_of_env_vars(buffer) + 1));
// 	while (buffer[++i])
// 	{
// 	}
// 	split_buffer[k] = 0;
// 	printf("%s\n", split_buffer[0]);
// 	printf("%s\n", split_buffer[1]);
// 	printf("%s\n", split_buffer[2]);
// 	return (0);
// }

int	here_doc_write(t_data_p *data, char *buffer, int idx)
{
	char	*tmp;

	if (data->commands[idx].expend_var)
		get_expend_var(data, buffer);
	if (!data->commands[idx].here_doc)
		data->commands[idx].here_doc = ft_strdup(buffer);
	else
	{
		tmp = data->commands[idx].here_doc;
		data->commands[idx].here_doc = ft_strjoin
			(data->commands[idx].here_doc, buffer);
		free(tmp);
	}
	return (0);
}

int	ft_here_doc(t_data_p *data, int idx)
{
	int		del_len;
	int		longest;
	char	*buffer;
	

	del_len = ft_strlen(data->commands[idx].here_doc_del);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		longest = del_len;
		if (ft_strlen(buffer) > (size_t)del_len)
			longest = (ft_strlen(buffer) - 1);
		if (!ft_strncmp(buffer
			, data->commands[idx].here_doc_del, longest))
			break;
		here_doc_write(data, buffer, idx);
		free(buffer);
	}
	free(buffer);
	return (0);
}
