/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 00:44:45 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/21 01:57:01 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_min(int	*src, int num)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] < num)
			return (0);
		i++;
	}
	return (1);
}

void	do_sleep(t_vals *vals, int sleep_time)
{
	int	start;

	start = vals->time;
	while (vals->time < start + sleep_time && vals->dead != 1)
		usleep(100);
}

int	dead_check(int dead)
{
	if (dead == 1)
	{
		usleep(1000000);
		return (1);
	}
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
