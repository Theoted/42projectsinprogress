/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:42:02 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/04 11:29:18 by tdeville         ###   ########lyon.fr   */
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

typedef struct s_philo t_philo;
typedef struct s_data t_data;


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
	pthread_t			status;
	pthread_mutex_t		speak;
	t_philo 			*philos;
};

struct s_philo
{
	int				id;
	int				running;
	long long int 	time_eat;
	int				eats;
	int				died;
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_data			*data;
};

// Utils functions //
int				ft_atoi(const char *str);
long long int	timems(void);
void			ft_usleep(int time);

// Execution
int				check_die_and_eat(t_data *data);
int				try_eat(t_philo *philo);
void			sleeping(t_philo *philo);
int				eats_number(t_philo *philo);
void			ft_mutex_lock(t_philo *philo);
void			ft_mutex_unlock(t_philo *philo);
void			thinking(t_philo *philo);
int				check_eats(t_philo *philo);

#endif
