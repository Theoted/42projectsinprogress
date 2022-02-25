/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:03:49 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/25 13:54:17 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_here_doc(char **av, int ac, t_pipex *data)
{
	char	*buffer;
	int		hd_file;

	hd_file = open(".hdfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(STDOUT_FILENO, "pipe heredoc> ", 15);
		buffer = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(buffer, av[2], (ft_strlen(buffer) - 1)))
			break ;
		write(hd_file, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(hd_file);
	data->infile = open(".hdfile", O_RDONLY);
	if (data->infile == -1)
		write(STDERR_FILENO, "infile not found or permission denied\n", 39);
	data->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data->outfile == -1)
		write(STDERR_FILENO, "outfile permission denied\n", 27);
	data->hd = 1;
	return (0);
}

int	check_hd(char **av, int ac, t_pipex *data)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_strncmp(av[i], "here_doc", 9))
		{
			data->nb_cmd = (ac - 4);
			return (1);
		}
		i++;
	}
	return (0);
}
