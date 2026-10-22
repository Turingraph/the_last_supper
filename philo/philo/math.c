/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phsottat <phsottat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:43:13 by phsottat          #+#    #+#             */
/*   Updated: 2026/10/22 12:43:14 by phsottat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * compute |x|
 */
int	f_abs(int x)
{
	if (x < 0)
		return (-1 * x);
	return (x);
}

/** 
 * if a > b, return b, else return a.
 */
int	f_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * if (num < min), return min.
 * if (num > max), return max.
 * else return num
 */
int	f_interval(int num, int min, int max)
{
	if (num > max)
		return (max);
	if (num < min)
		return (min);
	return (num);
}

/** 
 * convert any float number to integer by floor function.
 */
float	f_floor(float num)
{
	long long	n;
	float		d;

	if (num > 2147483647.0)
		return (2147483647.0);
	if (num < -2147483648.0)
		return (-2147483648.0);
	n = (long long)num;
	d = (float)n;
	return (d);
}

/** 
 * convert any float number to integer by round the number.
 */
float	f_round(float num)
{
	float	floor;

	floor = f_floor(num);
	if (num > 2147483647.0)
		return (2147483647.0);
	if (num < -2147483648.0)
		return (-2147483648.0);
	if (num - floor < floor + 1 - num)
		return (floor);
	return (floor + 1);
}
