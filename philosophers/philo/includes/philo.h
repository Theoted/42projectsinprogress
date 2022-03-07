/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:42:02 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/07 16:38:23 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int					ph_nb;
	int					die;
	int					sleep;
	int					eat;
	int					eat_nb;
	int					eats_done;
	int					check_eat;
	int					ph_dead;
	long long int		start;
	int					ready;
	pthread_mutex_t		speak;
	pthread_mutex_t		m_gettime;
	// pthread_mutex_t		speak;
	// pthread_mutex_t		speak;
	// pthread_mutex_t		speak;
	t_philo				*philos;
};

struct s_philo
{
	int				id;
	int				running;
	long long int	time_eat;
	int				eats;
	int				died;
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_data			*data;
};

// Utils functions //
int				ft_atoi(const char *str);
long long int	timems(void);
void			ft_usleep(int time, t_philo *philo);
int				check_for_end(t_philo *philo);
int				print_out(int id, char *str, t_philo *philo);

// Execution
int				check_die_and_eat(t_data *data);
int				eats_number(t_philo *philo);
int				fork_and_eat(t_philo *philo);
void			ft_mutex_unlock(t_philo *philo);
int				check_eats(t_philo *philo);
int				one_philo_eating(t_philo *philo);

// Actions
int				try_eat(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);

// Init
t_data			init_data(char **av);
void			init_philo(t_data *data);

#endif
