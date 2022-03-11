/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:04:51 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/11 15:32:24 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int	backslash_nb;
	int	j;

	backslash_nb = 0;
	while (arg[i] == ' ' && arg[i])
		i++;
	j = i;
	while (arg[i] != ' ' && arg[i])
		i++;
	data->commands[idx].here_doc_del = ft_substr(arg, j, i);
	return (0);
}

int	here_doc_write(t_data_p *data, char *buffer, int idx)
{
	char	*tmp;

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
