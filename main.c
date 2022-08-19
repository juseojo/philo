/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:34:56 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/19 23:02:14 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_can_eat(int max, int num, int *fork)
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

void end_eat(int max, int num, int *fork)
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

int	dead_do(t_dead dead)
{
	while (1)
	{
		if (dead.life - dead.vals->time < 0)
		{
			printf("%d %d died\n", dead.vals->time, dead.num);
			dead.vals->dead = 1;
			return (1);
		}
		usleep(100);
	}
	return (0);
}

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

void	philo_do(t_vals vals)
{
	int 		start;
	int			num;
	t_dead		dead;
	pthread_t	dead_thread;

	start = vals.time;
	dead.vals = &vals;
	dead.num = vals.philo_num + 1;
	num = vals.philo_num + 1;
	dead.life = vals.args.time_to_die;
	vals.ate[num - 1] = 0;
	pthread_create(&dead_thread, 0, dead_do, &dead);
	while (1)
	{
		pthread_mutex_lock(&vals.mutex_lock);
		if (dead.vals->dead != 1 && is_min(vals.ate, vals.ate[num - 1]) && check_can_eat(vals.args.number_of_philosophers - 1, num - 1, vals.fork))
		{
			pthread_mutex_unlock(&vals.mutex_lock);
			printf("%lld %d has taken a fork\n", vals.time, num);
			printf("%lld %d is eating\n", vals.time, num);
			dead.life = vals.time + vals.args.time_to_die;
			//pthread_mutex_lock(&vals.mutex_lock);
			vals.ate[num - 1] = vals.time;
			//pthread_mutex_unlock(&vals.mutex_lock);
			usleep(vals.args.time_to_eat * 1000);
			pthread_mutex_lock(&vals.mutex_lock);
			end_eat(vals.args.number_of_philosophers - 1, num - 1, vals.fork);
			pthread_mutex_unlock(&vals.mutex_lock);
			if (dead.vals->dead == 1)
				return ;
			printf("%lld %d is sleeping\n", vals.time, num);
			usleep(vals.args.time_to_sleep * 1000);
			if (dead.vals->dead == 1)
				return ;
			printf("%lld %d is thinking\n", vals.time, num);
			usleep(100);
		}
		pthread_mutex_unlock(&vals.mutex_lock);
		usleep(100);
	}
}

void time_do(t_vals vals)
{
	struct 			timeval start;

	gettimeofday(&vals.tv, 0);
	gettimeofday(&start, 0);
	while (1)
	{
		gettimeofday(&vals.tv, 0);
		pthread_mutex_lock(&vals.mutex_lock);
		vals.time =	(vals.tv.tv_sec - start.tv_sec) * 1000 + ((vals.tv.tv_usec - start.tv_usec) / 1000);
		pthread_mutex_unlock(&vals.mutex_lock);
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	t_vals			vals;
	pthread_t		*philo_threads;
	pthread_t		time_thread;
	int				cnt;

	if (argc != 5)
		return(0);
	vals.args.number_of_philosophers = ft_atoi(argv[1]);
	vals.args.time_to_die = ft_atoi(argv[2]);
	vals.args.time_to_eat = ft_atoi(argv[3]);
	vals.args.time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&vals.mutex_lock, 0);
	vals.fork = malloc(sizeof(int) * vals.args.number_of_philosophers);
	vals.ate = malloc(sizeof(int) * vals.args.number_of_philosophers);
	vals.philos = malloc(sizeof(int) * vals.args.number_of_philosophers);
	philo_threads = malloc(sizeof(pthread_t) * vals.args.number_of_philosophers);
	if (!vals.fork || !vals.philos || !philo_threads)
		exit (100);
	cnt = -1;
	pthread_create(&time_thread, 0, time_do, &vals);
	while (++cnt < vals.args.number_of_philosophers)
	{
		vals.philo_num = cnt;
		pthread_create((philo_threads + cnt * sizeof(pthread_t)), 0, philo_do, &vals);
		usleep(100);
	}
	while (vals.dead != 1)
	usleep(10000);
	return (1);
}
