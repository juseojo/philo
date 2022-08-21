/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 00:40:55 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/21 10:55:11 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_init(char *argv[], int argc, t_vals *vals)
{
	vals->args.number_of_philosophers = ft_atoi(argv[1]);
	vals->args.time_to_die = ft_atoi(argv[2]);
	vals->args.time_to_eat = ft_atoi(argv[3]);
	vals->args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		vals->args.must_eat = ft_atoi(argv[5]);
	else
		vals->args.must_eat = -1;
	if (argc == 6 && vals->args.must_eat < 0)
		return (0);
	if (vals->args.number_of_philosophers < 0 || vals->args.time_to_die < 0 \
	|| vals->args.time_to_eat < 0 || vals->args.time_to_sleep < 0)
		return (0);
	return (1);
}

int	init(char *argv[], int argc, t_vals *vals, pthread_t **philo_threads)
{
	if (!args_init(argv, argc, vals))
		return (0);
	vals->dead = 0;
	vals->philo_num = -1;
	vals->ends = 0;
	pthread_mutex_init(&vals->mutex_lock, 0);
	vals->fork = malloc(sizeof(int) * vals->args.number_of_philosophers);
	vals->ate = malloc(sizeof(int) * vals->args.number_of_philosophers);
	vals->philos = malloc(sizeof(int) * vals->args.number_of_philosophers);
	*philo_threads = malloc(sizeof(pthread_t) * \
	vals->args.number_of_philosophers);
	if (!vals->fork || !vals->philos || !*philo_threads || !vals->ate)
		return (0);
	return (1);
}

void	dead_init(t_dead	*dead, t_vals	*vals, pthread_t	*dead_thread)
{
	dead->vals = vals;
	dead->num = vals->philo_num + 1;
	dead->life = vals->args.time_to_die;
	dead->ate_cnt = 0;
	dead->stop = 0;
	pthread_create(dead_thread, 0, dead_do, dead);
	pthread_detach(*dead_thread);
}
