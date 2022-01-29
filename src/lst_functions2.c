/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:39:29 by tdeville          #+#    #+#             */
/*   Updated: 2022/01/29 13:11:39 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_lstclear1(t_cmds **lst, void (*del)(void *))
{
	t_cmds	*tmp;

	if (lst)
	{
		tmp = *lst;
		while (tmp)
		{
			tmp = (*lst)->next;
			ft_lstdelone1(*lst, (del));
			*lst = tmp;
		}
		*lst = NULL;
	}
}

void	ft_lstdelone1(t_cmds *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->cmd);
		free_all(lst->arg_vec_t);
		free(lst);
	}
}

void	del(char *str)
{
	free(str);
}

