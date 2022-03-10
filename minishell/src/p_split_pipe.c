/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:58:54 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/10 12:29:28 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// // static char	**freeall_p(char **str, int n)
// // {
// // 	n++;
// // 	while (n--)
// // 		free(str[n]);
// // 	free(str);
// // 	return (0);
// // }

// // static int	wordlen_p(char const *s, char c)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (s[i] && s[i] != c)
// // 		i++;
// // 	return (i);
// // }

// // static char	*ft_strndup_p(char const *s, size_t size)
// // {
// // 	size_t		i;
// // 	char		*word;

// // 	i = 0;
// // 	word = malloc((sizeof(char) * size) + 1);
// // 	if (!word)
// // 		return (0);
// // 	while (i < size && s[i])
// // 	{
// // 		word[i] = s[i];
// // 		i++;
// // 	}
// // 	word[i] = '\0';
// // 	return (word);
// // }


// // Cette fonction compte le nombre de pipe valide dans l'argument
// int	count_pipes(char const *s, t_data_p data)
// {
// 	int	count;
// 	int	i;
// 	int	j;

// 	count = 0;
// 	i = -1;
// 	while (s[++i])
// 	{
// 		if (s[i] == '|')
// 		{
// 			j = i;
// 			while (s[--j] && s[j] != '|')
// 			{
// 				if (s[j] == '\'')
// 					data.check_squotes++;
// 				if (s[j] == '\"')
// 					data.check_dquotes++;
// 			}
// 			if ((data.check_squotes % 2 == 0) && (data.check_dquotes % 2 == 0))
// 				count++;
// 		}
// 	}
// 	return (count);
// }

// char **lexer_pipes(char const *s, t_data_p data)
// {
// 	char	**args;
// 	int		i;
// 	int		j;
// 	int		k;
	
// 	args = malloc(sizeof(char *) * (count_pipes(s, data) + 2));
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (s[i])
// 	{
// 		if ((s[i] == '|') && pipe_ok(s, i, data))
// 		{
// 			args[j] = ft_substr(s, k, (i - k));
// 			// printf("arg[j] = %s.\n", args[j]);
// 			k = i + 1;
// 			j++;
// 		}
// 		if (s[i + 1] == 0)
// 		{
// 			args[j] = ft_substr(s, k, (i - k + 1));
// 			// printf("arg[j] = %s.\n", args[j]);
// 		}
// 		i++;
// 	}
// 	args[j + 1] = 0;
// 	return (args);
// }

// // Cette fonction va permettre au lexer de cheker si le pipe est valide
// // Elle check si il y a un nombre impaire de quote entre le pipe checké
// // et le pipe precedent (ou debut du fichier).
// // Cependant il peut y avoir un nombre impaire de quote mais le pipe peut
// // quand meme etre valide. La fonction pipe_before_quote va permettre
// // de checker ca
// int	pipe_ok(char const *s, size_t len, t_data_p data)
// {
// 	int	i;
// 	int	j;

// 	i = len;
// 	if (s[i] == '|')
// 	{
// 		j = i;
// 		while ((s[--i] != '|') && i)
// 		{
// 			if (s[i] == '\'')
// 				data.check_squotes++;
// 			if (s[i] == '\"')
// 				data.check_dquotes++;
// 		}
// 		if ((data.check_squotes % 2 == 0) && (data.check_dquotes % 2 == 0))
// 			return (1);
// 		else if (s[i - 1] == '|')
// 	}
// 	return (0);
// }

// // // Cett fonction permet de savoir si il ya un pipe avant un nombre
// // // impaire de quote ce qui veux dire que le pipe d'apres est valide
// // int	pipe_before_quote(char const *s, int i)
// // {
// // 	int	j;

// // 	j = 0;
// // 	while (s[i] != '|' && i)
// // 		i--;
// // 	if (s[i] == '|')
// // 		return (1);
// // 	return (0);
// // }

// char	**ft_split_p(char const *s, t_data_p data)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	char	**newstring;

// 	i = 0;
// 	j = -1;
// 	if (!s)
// 		return (0);
// 	size = count_pipes(s, data);
// 	newstring = malloc(sizeof(char *) * (size + 2));
// 	if (!newstring)
// 		return (0);
// 	while (++j < (size + 1) && *s)
// 	{
// 		printf("i = %d\n", i);
// 		i = pipe_ok(s, i, data);
// 		// if (!newstring[j])
// 		// 	return (freeall(newstring, j));
// 	}
// 	newstring[j] = 0;
// 	return (newstring);
// }
