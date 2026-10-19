#include "philosopher.h"

bool	f_is_loop(const t_philosopher *src)
{
	if (src == NULL)
		return (false);
	if (((0 < src->time_to_live && src->current_time < src->time_to_live)
		|| (src->time_to_live == 0)) && src->is_loop != NULL && *src->is_loop == true)
		return (true);
	return (false);
}

void	write_philosopher_biography(
	const t_philosopher *philosopher, t_philo_action action)
{
	clock_t current;

	current = clock();
	if (philosopher == NULL)
		return ;
	pthread_mutex_lock(philosopher->mutex);
	if (f_is_loop(philosopher) == false)
	{
		pthread_mutex_unlock(philosopher->mutex);
		return ;
	}
	ft_putnbr_fd(current, 1, "0123456789", 1);
	write(1, " ", 1);
	ft_putnbr_fd(philosopher->name + 1, 1, "0123456789", 1);
	write(1, " ", 1);
	if (action == E_ACT_FORK_L)
		write(1, "has taken a left fork", 21);
	if (action == E_ACT_FORK_R)
		write(1, "has taken a right fork", 22);
	if (action == E_ACT_THINK)
		write(1, "is thinking", 11);
	if (action == E_ACT_EAT)
		write(1, "is eating", 9);
	if (action == E_ACT_DIE)
		write(1, "die", 3);
	if (action == E_ACT_SLEEP)
		write(1, "is sleeping", 11);
	write(1, "(", 1);
	ft_putnbr_fd(philosopher->current_time, 1, "0123456789", 1);
	write(1, ")", 1);
	write(1, "\n", 1);
	pthread_mutex_unlock(philosopher->mutex);
}

void	locking_fork(t_philosopher *src, bool lock)
{
	if (lock == true && src->name % 2 == 0)
	{
		pthread_mutex_lock(src->fork_lock_l);
		write_philosopher_biography(src, E_ACT_FORK_L);
		pthread_mutex_lock(src->fork_lock_r);
		write_philosopher_biography(src, E_ACT_FORK_R);
	}
	if (lock == false && src->name % 2 == 0)
	{
		pthread_mutex_unlock(src->fork_lock_l);
		pthread_mutex_unlock(src->fork_lock_r);
	}
	if (lock == true && src->name % 2 == 1)
	{
		pthread_mutex_lock(src->fork_lock_r);
		write_philosopher_biography(src, E_ACT_FORK_R);
		pthread_mutex_lock(src->fork_lock_l);
		write_philosopher_biography(src, E_ACT_FORK_L);
	}
	if (lock == false && src->name % 2 == 1)
	{
		pthread_mutex_unlock(src->fork_lock_r);
		pthread_mutex_unlock(src->fork_lock_l);
	}
}

void	*philosopher_action(void *arg)
{
	t_philosopher	*philosopher;
	clock_t current;

	if (arg == NULL)
		return (NULL);
	philosopher = (t_philosopher *)arg;
	while (f_is_loop(philosopher) == true)
	{
		locking_fork(philosopher, true);
		usleep(philosopher->time_to_eat);
		current = clock();
		if (current - philosopher->prev_eat < philosopher->time_to_die)
			write_philosopher_biography(philosopher, E_ACT_EAT);
		else
		{
			write_philosopher_biography(philosopher, E_ACT_DIE);
			if (philosopher->is_loop != NULL)
			{
				pthread_mutex_lock(philosopher->mutex);
				*(philosopher->is_loop) = false;
				pthread_mutex_unlock(philosopher->mutex);
			}
		}
		philosopher->prev_eat = clock();
		locking_fork(philosopher, false);
		philosopher->current_time += 1;
		if (f_is_loop(philosopher) == true)
		{
			usleep(philosopher->time_to_sleep);
			write_philosopher_biography(philosopher, E_ACT_SLEEP);
		}
	}
	return (NULL);
}
