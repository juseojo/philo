/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjch <seongjch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:48:40 by seongjch          #+#    #+#             */
/*   Updated: 2022/08/21 10:53:41 by seongjch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\v'\
			|| ch == '\r' || ch == '\f')
	{
		return (1);
	}
	return (0);
}

static int	cut(const char	*str, int *i, int *j)
{
	int	minus;
	int	plus;

	*i = 0;
	*j = 0;
	minus = 0;
	plus = 0;
	while (str[*i] && !('0' <= str[*i] && str[*i] <= '9'))
	{
		if (str[*i] == '-')
			minus++;
		if (str[*i] == '+')
			plus++;
		if (str[*i] != '-' && str[*i] != '+' && !is_space(str[*i]))
			return (-1);
		if (minus + plus > 1)
			return (-1);
		if ((minus > 0 || plus > 0) && is_space(str[*i]))
			return (-1);
		*i = *i + 1;
	}
	if (minus)
		return (1);
	return (0);
}

static long	cul_result(const char *str, int sign, int *i, int *j)
{
	long	result;
	long	dig;

	dig = 1;
	result = 0;
	while (*j > 0)
	{
		result += (str[*i + *j - 1] - '0') * dig;
		if (result < (str[*i + *j - 1] - '0') * dig)
		{
			if (sign)
				return (0);
			else
				return (-1);
		}
		dig *= 10;
		*j = *j - 1;
	}
	return (result);
}

int	ft_atoi(const char	*str)
{
	int		i;
	int		j;
	int		sign_minus;
	long	result;

	sign_minus = cut(str, &i, &j);
	while (str[i + j])
	{
		if (!('0' <= str[i + j] && str[i + j] <= '9'))
			return (-1);
		j = j + 1;
	}
	result = cul_result(str, sign_minus, &i, &j);
	if (sign_minus == -1)
		exit (101);
	if (sign_minus)
		result = -result;
	return (result);
}
