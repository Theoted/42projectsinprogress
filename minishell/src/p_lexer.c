/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:17:25 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/10 17:55:57 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			if (!pipe_check(str, i))
				count++;
		i++;
	}
	return (count);
}

void	create_arg(char *str, int i, t_data_p *data, int bad_pipe)
{
	int		j;
	char	*arg;

	j = i;
	while (str[--j] != '|' && str[j] && j)
	{
		while (str[j - 1] == '|' && bad_pipe > 0)
		{
			j--;
			bad_pipe--;
		}
	}
	if (str[j] == '|')
		j++;
	arg = ft_substr(str, j, i - j);
	data->args[data->args_create] = ft_strtrim(arg, " ");
	data->args_create++;
	free(arg);
}

int	synthax_checker(char *arg)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && quote == 0)
			quote = arg[i];
		else if (arg[i] == quote && quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (1);
	return (0);
}

int	lexer(char *arg, t_data_p *data)
{
	int		i;
	int		bad_pipe;

	i = 0;
	bad_pipe = 0;
	data->pipes_nb = count_pipes(arg);
	data->args_create = 0;
	data->args = malloc(sizeof(char *) * (data->pipes_nb + 2));
	if (synthax_checker(arg))
	{
		printf("Synthax error\n");
		return (1);
	}
	while (arg[i])
	{
		// if (arg[i] == '$')
		// 	dollar_check();
		if (arg[i] == '|')
		{
			if (!pipe_check(arg, i))
			{
				create_arg(arg, i, data, bad_pipe);
				bad_pipe = 0;
			}
			else
				bad_pipe++;
		}
		i++;
	}
	create_arg(arg, i, data, bad_pipe);
	data->args[data->args_create] = 0;
	return (0);
}

int	pipe_check(char *arg, int i)
{
	char	quote;
	int		j;
	
	quote = 0;
	j = 0;
	while (j < i)
	{
		if ((arg[j] == '\'' || arg[j] == '\"') && quote == 0)
			quote = arg[j];
		else if (arg[j] == quote && quote)
			quote = 0;
		j++;
	}
	if (quote)
		return (1);
	return (0);
}

int	pipe_synthax(char *str, t_data_p data)
{
	int	i;
	int	valid_pipe_nb;

	i = 0;
	valid_pipe_nb = 0;
	while (str[i])
	{
		if (str[i] == '|' && (!pipe_check(str, i)))
			valid_pipe_nb++;
		if (str[i] == '|' && (!pipe_check(str, i))
			&& valid_pipe_nb == data.pipes_nb)
		{
			while (str[++i])
				if (ft_isalpha(str[i]))
					return (1);
		}
		i++;
	}
	return (0);
}
