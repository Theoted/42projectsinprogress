/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:21:05 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/10 17:38:11 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_args		args;
	t_data_p	data_p;
	
	(void)ac;
	(void)av;
	find_env_path(envp, &args);
	while (1)
	{
		args.stdin_arg = readline("\033[0;34mShellDePetiteTaille-0.0.42: \033[0m");
		lexer(args.stdin_arg, &data_p);
		printf("%s\n", data_p.args[0]);
		printf("%s\n", data_p.args[1]);
		printf("%s\n", data_p.args[2]);
		printf("%s\n", data_p.args[3]);
	}
	return (0);
}