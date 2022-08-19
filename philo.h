/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:48:43 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/19 22:12:09 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
#include <sys/time.h>
# include <unistd.h>

typedef struct s_args {
	long long	number_of_philosophers;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
}	t_args;

typedef struct s_vals {
	t_args			args;
	long long		philo_num;
	long long		time;
	int				dead;
	int				*fork;
	int				*ate;
	int				*philos;
	struct 			timeval tv;
	pthread_mutex_t mutex_lock;
}	t_vals;

typedef struct s_dead {
	t_vals		*vals;
	long long	life;
	int			num;
}	t_dead;

int	ft_atoi(const char	*str);

#endif
