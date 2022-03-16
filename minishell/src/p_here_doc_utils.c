/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_here_doc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:28:03 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/16 14:33:17 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	check_var(char *var)
{
	if (var[0] == '$')
	{
		if (var[1] == '\'' || var[1] == '\"')
			return (1);
		return (0);
	}
	return (1);
}
