/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phsottat <phsottat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:33:59 by phsottat          #+#    #+#             */
/*   Updated: 2026/10/23 13:13:52 by phsottat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	f_is_loop(const t_philo *src)
{
	if (src == NULL)
		return (false);
	if (((0 < src->time_to_live && src->current_iter < src->time_to_live)
			|| (src->time_to_live == 0))
		&& src->is_loop != NULL && *src->is_loop == true)
		return (true);
	return (false);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	write_philo_record_unit(t_philo_action action)
{
	if (action == E_ACT_FORK_L)
		write(1, "L", 1);
		// write(1, "has taken a left fork", 21);
	if (action == E_ACT_FORK_R)
		write(1, "R", 1);
		// write(1, "has taken a right fork", 22);
	if (action == E_ACT_THINK)
		write(1, "is thinking", 11);
	if (action == E_ACT_EAT)
		write(1, "is eating", 9);
	if (action == E_ACT_DIE)
		write(1, "die", 3);
	if (action == E_ACT_SLEEP)
		write(1, "is sleeping", 11);
}

void	write_philo_record(
	const t_philo *philo, t_philo_action action)
{
	clock_t	current;

	if (philo == NULL)
		return ;
	pthread_mutex_lock(philo->mutex);
	if (*philo->current_time == 0)
	{
		current = 0;
		*philo->current_time = clock();
	}
	else
	{
		current = clock() - *philo->current_time;
	}
	if (f_is_loop(philo) == false)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	ft_putnbr_fd(current, 1, "0123456789", 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->name + 1, 1, "0123456789", 1);
	write(1, " ", 1);
	write_philo_record_unit(action);
	write(1, "\n", 1);
	pthread_mutex_unlock(philo->mutex);
}

// write(1, "(", 1);
// ft_putnbr_fd(philo->current_iter, 1, "0123456789", 1);
// write(1, ")", 1);
