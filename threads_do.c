/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 00:42:39 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/21 17:46:04 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_do(void *argu)
{
	t_dead	*dead;

	dead = argu;
	while (dead->stop != 1 && dead->vals->dead != 1)
	{
		pthread_mutex_lock(&dead->vals->mutex_lock);
		if (dead->vals->dead == 1)
		{
			pthread_mutex_unlock(&dead->vals->mutex_lock);
			return (NULL);
		}
		if (dead->life - dead->vals->time <= 0)
		{
			dead->vals->dead = 1;
			pthread_mutex_unlock(&dead->vals->mutex_lock);
			usleep(1000);
			printf("%lld %d died\n", dead->vals->time, dead->num);
			return (NULL);
		}
		pthread_mutex_unlock(&dead->vals->mutex_lock);
		usleep(300);
	}
	return (NULL);
}

void	*philo_do(void *argu)
{
	t_dead		dead;
	t_vals		*vals;
	pthread_t	dead_thread;

	vals = argu;
	dead_init(&dead, vals, &dead_thread);
	while (dead.vals->dead != 1)
	{
		pthread_mutex_lock(&vals->mutex_lock);
		if (is_min(vals->ate, vals->args.number_of_philosophers, vals->\
		ate[dead.num - 1]) && dead.vals->dead != 1 \
		&& check_can_eat(vals->args.number_of_philosophers - 1, \
		dead.num - 1, &vals->fork))
		{
			if (philo_life(vals, &dead, dead.num))
				return (NULL);
		}
		else
			pthread_mutex_unlock(&vals->mutex_lock);
		usleep(200);
		if (dead_check(dead.vals->dead))
			return (NULL);
	}
	usleep(1000000);
	return (NULL);
}

void	*time_do(void *argu)
{
	struct timeval	start;
	t_vals			*vals;

	vals = argu;
	gettimeofday(&vals->tv, 0);
	gettimeofday(&start, 0);
	while (vals->dead != 1 && vals->ends != vals->args.number_of_philosophers)
	{
		gettimeofday(&vals->tv, 0);
		pthread_mutex_lock(&vals->mutex_lock);
		vals->time = (vals->tv.tv_sec - start.tv_sec) * 1000 + \
		((vals->tv.tv_usec - start.tv_usec) / 1000);
		pthread_mutex_unlock(&vals->mutex_lock);
		usleep(100);
	}
	return (NULL);
}
