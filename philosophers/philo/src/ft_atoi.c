/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:00:11 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/07 16:01:44 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static int	check_sign(int sign)
{
	if (sign < 0)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		res;
	int		neg;
	int		i;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if ((long int)res > 2147483647)
			return (check_sign(neg));
	}
	return (res * neg);
}