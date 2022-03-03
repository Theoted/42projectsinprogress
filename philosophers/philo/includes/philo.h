/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:42:02 by tdeville          #+#    #+#             */
/*   Updated: 2022/03/03 16:54:00 by tdeville         ###   ########lyon.fr   */
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

// Execution
int				check_die(t_data *data);
int				try_eat(t_philo *philo);
int				sleeping(t_philo *philo);
int				eats_number(t_philo *philo);

#endif
