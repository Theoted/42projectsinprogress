/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:01:31 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/24 11:51:22 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			length;
	unsigned int	j;
	char			*str;

	i = 0;
	j = start;
	length = len;
	if (!s)
		return (0);
	if (ft_strlen(s) < len)
		length = ft_strlen(s) - 1;
	str = malloc((sizeof(char) * length) + 1);
	if (!str)
		return (0);
	while (i < len && s[j] && (j < ft_strlen(s)))
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
