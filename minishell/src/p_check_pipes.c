/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:36:15 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/09 18:09:20 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	split_pipes(char *line)
// {
	
// }

int	check_pipe(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
			if (!pipe_not_in_quotes(line))
				return (1);
	}
	return (0);
}

int	pipe_not_in_quotes(char *line)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
	{
		if (ft_isquotes(line[i]))
		{
			j = i;
			while (line[++j] != line[i])
			{
				if (line[j] == '|')
					return (1);
			}
		}
	}
	return (0);
}
