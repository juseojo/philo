/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 00:42:39 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/23 17:21:18 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_do(void *argu)
{
	t_dead	*dead;

	dead = argu;
	while (1)
	{
		pthread_mutex_lock(&dead->vals->dead_lock);
		if (dead->vals->dead == 1 || dead->vals->ends == \
		dead->vals->args.number_of_philosophers)
		{
			pthread_mutex_unlock(&dead->vals->dead_lock);
			return (NULL);
		}
		if (*dead->life - now_time(dead->vals->start_time) <= 0)
		{
			dead->vals->dead = 1;
			pthread_mutex_unlock(&dead->vals->dead_lock);
			usleep(1000);
			printf("%lld %d died\n", now_time(dead->vals->start_time), dead->num);
			return (NULL);
		}
		pthread_mutex_unlock(&dead->vals->dead_lock);
		usleep(500);
	}
	return (NULL);
}

void	*philo_do(void *argu)
{
	t_dead		dead;
	t_vals		*vals;
	pthread_t	dead_thread;
	long long	life;

	vals = argu;
	dead_init(&dead, vals, &dead_thread, &life);
	while (1)
	{
		if (is_min(vals, dead.num - 1) \
		&& check_can_eat(vals, dead.num - 1))
		{
			if (philo_life(vals, &dead, dead.num))
				return (NULL);
		}
		usleep(500);
		if (dead_check(dead.vals))
			return (NULL);
	}
	usleep(1000000);
	return (NULL);
}
