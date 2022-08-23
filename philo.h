/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:48:43 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/23 21:29:13 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args {
	long long	number_of_philosophers;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	must_eat;
}	t_args;

typedef struct s_vals {
	t_args			args;
	long long		philo_num;
	int				dead;
	int				ends;
	int				*fork;
	int				*ate;
	int				*philos;
	struct timeval	start_time;
	pthread_mutex_t	mutex_lock;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	ate_lock;
}	t_vals;

typedef struct s_dead {
	t_vals		*vals;
	long long	*life;
	int			num;
	int			ate_cnt;
}	t_dead;

int			ft_atoi(const char	*str);
int			init(char *argv[], int argc, t_vals *vals, \
pthread_t **philo_threads);
void		dead_init(t_dead *dead, t_vals *vals, pthread_t \
*dead_thread, long long *life);
void		*dead_do(void *argu);
void		*philo_do(void *argu);
void		*time_do(void *argu);
int			is_min(t_vals *vals, int num);
void		do_sleep(t_vals *vals, int sleep_time);
int			dead_check(t_vals *vals);
int			check_can_eat(t_vals *vals, int num);
int			philo_life(t_vals *vals, t_dead *dead, \
int num);
void		ending(t_vals *vals);
long long	now_time(struct timeval start_time);

#endif
