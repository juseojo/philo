/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 00:44:45 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/23 21:27:57 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_min(t_vals *vals, int num)
{
	int	i;

	i = 0;
	while (i < vals->args.number_of_philosophers)
	{
		pthread_mutex_lock(&vals->ate_lock);
		if (vals->ate[i] < vals->ate[num])
		{
			pthread_mutex_unlock(&vals->ate_lock);
			return (0);
		}
		pthread_mutex_unlock(&vals->ate_lock);
		i++;
	}
	return (1);
}

long long	now_time(struct timeval start_time)
{
	struct timeval	now;

	gettimeofday(&now, 0);
	return ((now.tv_sec * 1000 - start_time.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start_time.tv_usec / 1000));
}

void	do_sleep(t_vals *vals, int sleep_time)
{
	int	now;
	int	start;

	start = now_time(vals->start_time);
	usleep(sleep_time * 9 / 10);
	now = now_time(vals->start_time);
	while (now < start + sleep_time)
	{
		if (dead_check(vals))
			break ;
		usleep(500);
		now = now_time(vals->start_time);
	}
}

int	dead_check(t_vals *vals)
{
	pthread_mutex_lock(&vals->dead_lock);
	if (vals->dead == 1 || vals->ends == \
	vals->args.number_of_philosophers)
	{
		pthread_mutex_unlock(&vals->dead_lock);
		usleep(1000000);
		return (1);
	}
	pthread_mutex_unlock(&vals->dead_lock);
	return (0);
}

void	ending(t_vals *vals)
{
	usleep(1000000);
	pthread_mutex_destroy(&vals->mutex_lock);
	pthread_mutex_destroy(&vals->ate_lock);
	pthread_mutex_destroy(&vals->dead_lock);
	pthread_mutex_destroy(&vals->fork_lock);
	free(vals->fork);
	free(vals->ate);
	free(vals->philos);
}
