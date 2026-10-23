/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phsottat <phsottat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:33:16 by phsottat          #+#    #+#             */
/*   Updated: 2026/10/23 13:13:42 by phsottat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	locking_fork(t_philo *src, bool lock)
{
	if (lock == true && src->name % 2 == 0)
	{
		pthread_mutex_lock(src->fork_lock_l);
		write_philo_record(src, E_ACT_FORK_L);
		pthread_mutex_lock(src->fork_lock_r);
		write_philo_record(src, E_ACT_FORK_R);
	}
	if (lock == false && src->name % 2 == 0)
	{
		pthread_mutex_unlock(src->fork_lock_l);
		pthread_mutex_unlock(src->fork_lock_r);
	}
	if (lock == true && src->name % 2 == 1)
	{
		pthread_mutex_lock(src->fork_lock_r);
		write_philo_record(src, E_ACT_FORK_R);
		pthread_mutex_lock(src->fork_lock_l);
		write_philo_record(src, E_ACT_FORK_L);
	}
	if (lock == false && src->name % 2 == 1)
	{
		pthread_mutex_unlock(src->fork_lock_r);
		pthread_mutex_unlock(src->fork_lock_l);
	}
}

/*
time_to_die milliseconds since the start of their last meal or the start of the
simulation, they die.
*/

void	*philo_action(void *arg)
{
	t_philo	*philo;
	clock_t	current;

	if (arg == NULL)
		return (NULL);
	philo = (t_philo *)arg;
	while (f_is_loop(philo) == true)
	{
		locking_fork(philo, true);
		current = clock();
		if (current - philo->prev_eat < philo->time_to_die)
			write_philo_record(philo, E_ACT_EAT);
		else
		{
			write_philo_record(philo, E_ACT_DIE);
			if (philo->is_loop != NULL)
			{
				pthread_mutex_lock(philo->mutex);
				*(philo->is_loop) = false;
				pthread_mutex_unlock(philo->mutex);
			}
		}
		usleep(philo->time_to_eat);
		locking_fork(philo, false);
		philo->prev_eat = clock();
		if (philo->time_to_live > 0)
			philo->current_iter += 1;
		if (f_is_loop(philo) == true)
		{
			write_philo_record(philo, E_ACT_SLEEP);
			usleep(philo->time_to_sleep);
			write_philo_record(philo, E_ACT_THINK);
		}
	}
	return (NULL);
}
