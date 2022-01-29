/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 10:01:09 by tdeville          #+#    #+#             */
/*   Updated: 2022/01/29 13:06:42 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	error(char *err, int n, t_pipex data)
{
	if (data.check == 1)
		write(STDERR_FILENO, "Permission denied\n", 19);
	if (err)
	{
		write(STDERR_FILENO, err, ft_strlen(err));
		free(err);
	}
	exit(1);
}

int	double_arrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

