/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:28:34 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/03 10:47:40 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

typedef struct s_test t_test;
typedef	struct s_tab t_tab;

struct s_tab
{
	t_test *lst;
};

struct s_test
{
//	int				a;
	int				b;
//	int				id;
	pthread_t		thread;
//	pthread_mutex_t	mutex;
//	t_tab			*tab;
};

void	change_value(t_test *t)
{
	int	i;

	i = 0;
	while (i < 1000000001)
	{
		i++;
		if (i == 1000000000)
		{
			if (t->b == 0)
			{
				printf("0\n");
				t->b = 1;
			}
			else
			{
				printf("1\n");
				t->b = 0;
			}
			i = 0;
		}
	}
}

void	*routine(void *arg)
{
	t_test *t;

	t = arg;
	change_value(t);
	return (NULL);
}

int main(int ac, char **av)
{
	// t_tab 		tab;
	t_test			*one;
	
	(void)ac;
	(void)av;
	one = malloc(sizeof(t_test));
	// tab.lst = malloc(sizeof(t_test *) * ft_atoi(av[1]));
	// for (int i = 0; i < ft_atoi(av[1]); i++)
	// {
	// 	tab.lst[i].id = i;
	// 	tab.lst[i].b = 0;
	// 	tab.lst[i].tab = &tab;
	// 	pthread_mutex_init(&tab.lst[i].mutex, NULL);
	// }
	one->b = 0;
	printf("test\n");
	pthread_create(&one->thread, NULL, &routine, one);
	// pthread_create(&tab.lst[0].thread, NULL, &routine, &tab.lst[0]);
	int	i = 0;
	while (1)
	{
		while (i < 100000001)
		{
			if (one->b == 1)
				printf("Oui\n");
			i++;
			if (i == 100000000)
				break ;
		}
		i = 0;
	}
	return (0);
}
