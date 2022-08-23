/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:34:56 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/23 17:15:37 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_can_eat(t_vals *vals, int num)
{
	int	max;

	max = vals->args.number_of_philosophers - 1;
	if (max == 0)
		return (0);
	pthread_mutex_lock(&vals->fork_lock);
	if (num != max && vals->fork[num] != 1 && vals->fork[num + 1] != 1)
	{
		vals->fork[num] = 1;
		vals->fork[num + 1] = 1;
		pthread_mutex_unlock(&vals->fork_lock);
		return (1);
	}
	else if (num == max && vals->fork[num] != 1 && vals->fork[0] != 1)
	{
		vals->fork[num] = 1;
		vals->fork[0] = 1;
		pthread_mutex_unlock(&vals->fork_lock);
		return (1);
	}
	pthread_mutex_unlock(&vals->fork_lock);
	return (0);
}

void	end_eat(t_vals *vals, int max, int num, int **fork)
{
	pthread_mutex_lock(&vals->fork_lock);
	if (num != max)
	{
		(*fork)[num] = 0;
		(*fork)[num + 1] = 0;
	}
	else if (num == max)
	{
		(*fork)[num] = 0;
		(*fork)[0] = 0;
	}
	pthread_mutex_unlock(&vals->fork_lock);
}

void	have_meal(t_vals *vals, t_dead **dead, int num)
{
	printf("%lld %d has taken a fork\n", now_time(vals->start_time), num);
	printf("%lld %d has taken a fork\n", now_time(vals->start_time), num);
	printf("%lld %d is eating\n", now_time(vals->start_time), num);
	pthread_mutex_lock(&vals->dead_lock);
	*(*dead)->life = now_time(vals->start_time) + vals->args.time_to_die;
	pthread_mutex_unlock(&vals->dead_lock);
	pthread_mutex_lock(&vals->ate_lock);
	vals->ate[num - 1] = now_time(vals->start_time);
	pthread_mutex_unlock(&vals->ate_lock);
	do_sleep(vals, vals->args.time_to_eat);
	end_eat(vals, vals->args.number_of_philosophers - 1, num - 1, &vals->fork);
}

int	philo_life(t_vals *vals, t_dead *dead, int num)
{
	have_meal(vals, &dead, num);
	if (++dead->ate_cnt == dead->vals->args.must_eat)
	{
		pthread_mutex_lock(&vals->dead_lock);
		dead->vals->ends += 1;
		pthread_mutex_unlock(&vals->dead_lock);
		usleep(1000);
	}
	usleep(100);
	if (dead_check(dead->vals))
		return (1);
	pthread_mutex_lock(&vals->dead_lock);
	printf("%lld %d is sleeping\n", now_time(vals->start_time), dead->num);
	pthread_mutex_unlock(&vals->dead_lock);
	do_sleep(vals, vals->args.time_to_sleep);
	usleep(100);
	if (dead_check(dead->vals))
		return (1);
	printf("%lld %d is thinking\n", now_time(vals->start_time), dead->num);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vals			vals;
	pthread_t		*philo_threads;

	if (argc != 5 && argc != 6)
		return (0);
	if (!init(argv, argc, &vals, &philo_threads))
		return (0);
	while (++vals.philo_num < vals.args.number_of_philosophers)
	{
		pthread_mutex_lock(&vals.ate_lock);
		vals.ate[vals.philo_num] = -1;
		pthread_mutex_unlock(&vals.ate_lock);
		pthread_create((philo_threads + vals.philo_num * sizeof(pthread_t)), \
		0, philo_do, &vals);
		pthread_detach(*(philo_threads + vals.philo_num * sizeof(pthread_t)));
		usleep(500);
	}
	while (vals.dead != 1 && vals.ends != vals.args.number_of_philosophers)
		usleep(100);
	ending(&vals);
	free(philo_threads);
	return (1);
}
