/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phsottat <phsottat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:27:52 by phsottat          #+#    #+#             */
/*   Updated: 2026/10/23 12:18:54 by phsottat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo_unit(size_t i,
	size_t length,
	pthread_mutex_t *fork_lock,
	pthread_mutex_t *mutex)
{
	t_philo	dst;

	dst.name = i;
	dst.length = length;
	dst.is_pick_left = false;
	dst.is_pick_right = false;
	dst.current_iter = 0;
	dst.time_to_live = 0;
	dst.time_to_eat = 100;
	dst.current_time = NULL;
	dst.time_to_sleep = 100;
	dst.prev_eat = clock();
	dst.is_loop = NULL;
	if (fork_lock != NULL)
	{
		dst.fork_lock_l = fork_lock + i;
		dst.fork_lock_r = fork_lock + (i + 1) % length;
	}
	else
	{
		dst.fork_lock_l = NULL;
		dst.fork_lock_r = NULL;
	}
	dst.mutex = mutex;
	return (dst);
}

t_philo	*init_philo_arr(size_t length,
	pthread_mutex_t *fork_lock,
	pthread_mutex_t *mutex)
{
	t_philo	*dst;
	size_t	i;

	if (length < 2 || fork_lock == NULL)
		return (NULL);
	dst = malloc_talk(sizeof(t_philo) * length, "philo\n");
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dst[i] = init_philo_unit(i, length, fork_lock, mutex);
		i += 1;
	}
	return (dst);
}

void	update_philos(t_philo *dst,
	size_t value, t_timetodo key, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (key == E_TIMETOLIVE)
			dst[i].time_to_live = value;
		if (key == E_TIMETOEAT)
			dst[i].time_to_eat = value;
		if (key == E_TIMETODIE)
			dst[i].time_to_die = value;
		if (key == E_TIMETOSLEEP)
			dst[i].time_to_sleep = value;
		i += 1;
	}
}

pthread_mutex_t	*init_multisems(size_t length)
{
	pthread_mutex_t	*dst;
	size_t			i;

	if (length < 1)
		return (NULL);
	dst = malloc_talk(sizeof(pthread_mutex_t) * length, "init_sem\n");
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		pthread_mutex_init(dst + i, NULL);
		i += 1;
	}
	return (dst);
}
