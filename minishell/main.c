/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:21:05 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/09 18:43:57 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_data(t_data_p *data_p)
{
	data_p->check_dquotes = 0;
	data_p->check_squotes = 0;
	data_p->exit = 0;
}

int main(int ac, char **av, char **envp)
{
	t_args		args;
	t_data_p	data_p;
	
	(void)ac;
	(void)av;
	find_env_path(envp, &args);
	init_data(&data_p);
	while (!data_p.exit)
	{
		args.stdin_arg = readline("\033[0;34mShellDePetiteTaille-0.0.42: \033[0m");
		printf("%d\n", count_pipes(args.stdin_arg, data_p));
	}
	return (0);
}