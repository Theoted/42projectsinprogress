/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:58:54 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/09 18:44:42 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static char	**freeall_p(char **str, int n)
// {
// 	n++;
// 	while (n--)
// 		free(str[n]);
// 	free(str);
// 	return (0);
// }

// static int	wordlen_p(char const *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] && s[i] != c)
// 		i++;
// 	return (i);
// }

// static char	*ft_strndup_p(char const *s, size_t size)
// {
// 	size_t		i;
// 	char		*word;

// 	i = 0;
// 	word = malloc((sizeof(char) * size) + 1);
// 	if (!word)
// 		return (0);
// 	while (i < size && s[i])
// 	{
// 		word[i] = s[i];
// 		i++;
// 	}
// 	word[i] = '\0';
// 	return (word);
// }

int	count_pipes(char const *s, t_data_p data)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '|')
		{
			j = i;
			while (s[--j] && s[j] != '|')
			{
				if (s[j] == '\'')
					data.check_squotes++;
				if (s[j] == '\"')
					data.check_dquotes++;
			}
			if ((data.check_squotes % 2 == 0) && (data.check_dquotes % 2 == 0))
				count++;
		}
	}
	return (count);
}

// static int	count_word_p(char const *s, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (*s && *s != c)
// 			count++;
// 		while (*s && *s != c)
// 			s++;
// 	}
// 	return (count);
// }

// char	**ft_split_p(char const *s, char c)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	char	**newstring;

// 	i = 0;
// 	j = -1;
// 	if (!s)
// 		return (0);
// 	size = count_word(s, c);
// 	newstring = malloc(sizeof(char *) * (count_word(s, c) + 1));
// 	if (!newstring)
// 		return (0);
// 	while (++j < size && *s)
// 	{
// 		while (*s == c)
// 			s++;
// 		i = wordlen(s, c);
// 		newstring[j] = ft_strndup(s, i);
// 		if (!newstring[j])
// 			return (freeall(newstring, j));
// 		s += i;
// 	}
// 	newstring[j] = 0;
// 	return (newstring);
// }

