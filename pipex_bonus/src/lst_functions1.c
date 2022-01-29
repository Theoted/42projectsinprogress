/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:12:22 by tdeville          #+#    #+#             */
/*   Updated: 2022/01/29 12:24:42 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_cmds	*ft_lstnew_double(char *cmd, char **arg_vec)
{
	t_cmds	*new;
	int		i;

	new = malloc(sizeof(t_cmds));
	new->arg_vec_t = malloc(sizeof(char *)
		* double_arrlen(arg_vec));
	i = 0;
	if (new)
	{
		new->cmd = cmd;
		while (arg_vec[i])
		{
			new->arg_vec_t[i] = ft_strdup(arg_vec[i]);
			i++;
		}
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back1(t_cmds **alst, t_cmds *new)
{
	t_cmds	*tmp;

	if (*alst)
	{
		tmp = ft_lstlast1(*alst);
		tmp->next = new;
	}
	else
		*alst = new;
}

t_cmds	*ft_lstlast1(t_cmds *lst)
{
	size_t	lstsize;
	size_t	i;

	lstsize = ft_lstsize1(lst);
	i = -1;
	if (!lst)
		return (0);
	while (++i < lstsize - 1)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize1(t_cmds *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_front1(t_cmds **alst, t_cmds *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

