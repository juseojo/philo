/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:34:56 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/21 00:50:21 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_can_eat(int max, int num, int *fork)
{
	if (num != max && fork[num] != 1 && fork[num + 1] != 1)
	{
		fork[num] = 1;
		fork[num + 1] = 1;
		return (1);
	}
	else if (num == max && fork[num] != 1 && fork[0] != 1)
	{
		fork[num] = 1;
		fork[0] = 1;
		return (1);
	}
	return (0);
}

void	end_eat(int max, int num, int *fork)
{
	if (num != max)
	{
		fork[num] = 0;
		fork[num + 1] = 0;
	}
	else if (num == max)
	{
		fork[num] = 0;
		fork[0] = 0;
	}
}

int	philo_life(t_vals *vals, t_dead *dead, int num)
{
	pthread_mutex_unlock(&vals->mutex_lock);
	printf("%lld %d has taken a fork\n", vals->time, num);
	printf("%lld %d is eating\n", vals->time, num);
	pthread_mutex_lock(&vals->mutex_lock);
	dead->life = vals->time + vals->args.time_to_die;
	pthread_mutex_unlock(&vals->mutex_lock);
	vals->ate[num - 1] = vals->time;
	do_sleep(vals, vals->args.time_to_eat);
	pthread_mutex_lock(&vals->mutex_lock);
	end_eat(vals->args.number_of_philosophers - 1, num - 1, vals->fork);
	pthread_mutex_unlock(&vals->mutex_lock);
	usleep(100);
	if (dead_check(dead->vals->dead))
		return (1);
	printf("%lld %d is sleeping\n", vals->time, dead->num);
	do_sleep(vals, vals->args.time_to_sleep);
	usleep(100);
	if (dead_check(dead->vals->dead))
		return (1);
	printf("%lld %d is thinking\n", vals->time, dead->num);
	return (0);
}

void	ending(t_vals *vals)
{
	usleep(10000);
	pthread_mutex_destroy(&vals->mutex_lock);
	free(vals->fork);
	free(vals->ate);
	free(vals->philos);
}

int	main(int argc, char *argv[])
{
	t_vals			vals;
	pthread_t		*philo_threads;
	pthread_t		time_thread;

	if (argc != 5 && argc != 6)
		return (0);
	if (!init(argv, argc, &vals, &philo_threads))
		return (0);
	pthread_create(&time_thread, 0, time_do, &vals);
	pthread_detach(time_thread);
	while (++vals.philo_num < vals.args.number_of_philosophers)
	{
		vals.ate[vals.philo_num] = -1;
		pthread_create((philo_threads + vals.philo_num * sizeof(pthread_t)), \
		0, philo_do, &vals);
		pthread_detach(*(philo_threads + vals.philo_num * sizeof(pthread_t)));
		usleep(100);
	}
	while (vals.dead != 1)
		usleep(100);
	ending(&vals);
	free(philo_threads);
	return (1);
}
