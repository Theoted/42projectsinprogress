/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:28:34 by tdeville          #+#    #+#             */
/*   Updated: 2022/02/23 13:22:43 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

typedef struct s_test t_test;
typedef	struct s_tab t_tab;

struct s_tab
{
	t_test *tab;
};

struct s_test
{
	int				a;
	int				b;
	int				id;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_tab			tab;
};


int	test_mutex(t_test t, int i)
{
	if (i > 0) {
		pthread_mutex_lock(&t.mutex);
		printf("%d lock his mutex\n", t.id);
		pthread_mutex_lock(&t.tab.tab[i - 1].mutex);
		printf("%d lock %d mutex\n", t.id, t.id - 1);
		pthread_mutex_destroy(&t.mutex);
		pthread_mutex_destroy(&t.tab.tab[i - 1].mutex);
		printf("%d %d mutex destroyed\n\n", t.id, t.id - 1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_test t;

	t = *(t_test *)arg;
	if ((t.id % 2) == 0)
		test_mutex(t, t.id);
	else
	{
		usleep(1000);
		test_mutex(t, t.id);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_tab 		tab;

	(void)ac;
	tab.tab = malloc(sizeof(t_test) * ft_atoi(av[1]));
	for (int i = 0; i < ft_atoi(av[1]); i++)
	{
		tab.tab[i].id = i;
		tab.tab[i].tab = tab;
		pthread_mutex_init(&tab.tab[i].mutex, NULL);
	}
	for (int i = 0; i < ft_atoi(av[1]); i++)
		if (pthread_create(&tab.tab[i].thread, NULL, &routine, &tab.tab[i]) == -1)
			printf("pthread create %d error\n", i);
	for (int i = 0; i < ft_atoi(av[1]); i++)
		if (pthread_join(tab.tab[i].thread, NULL) == -1)
			printf("pthread join %d error\n", i);
	return (0);
}