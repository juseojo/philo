/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:34:56 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/08 15:31:08 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_do(int philo_num)
{
	printf("%d philo run\n", philo_num);
	wait(100000);
}

int	main(int argc, char *argv[])
{
	t_args			args;
	pthread_mutex_t	mutex_lock;
	pthread_t		*philos;
	int				cnt;

	if (argc != 5)
		exit(0);
	args.number_of_philosophers = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	philos = malloc(sizeof(pthread_t) * args.number_of_philosophers);
	cnt = -1;
	while (++cnt < args.number_of_philosophers)
		pthread_create((philos + cnt * 8), NULL, philo_do, cnt);
}
