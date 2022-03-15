/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:21:05 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/14 11:43:04 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_data_p		data_p;
	
	(void)ac;
	(void)av;
	find_env_path(envp, &data_p);
	data_p.env_vars = envp;
	while (1)
	{
		data_p.stdin_arg = readline("\033[0;34mShellDePetiteTaille-0.0.42: \033[0m");
		if (data_p.stdin_arg[0])
			lexer(data_p.stdin_arg, &data_p);
	}
	return (0);
}