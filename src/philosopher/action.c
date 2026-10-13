#include "philosopher.h"

void	write_philosopher_biography(
	const t_philosopher *philosopher, t_philo_action action)
{
	clock_t current;

	current = clock();
	if (philosopher == NULL)
		return ;
	pthread_mutex_lock(philosopher->mutex);
	ft_putnbr_fd(current, 1, "0123456789", 1);
	write(1, " ", 1);
	ft_putnbr_fd(philosopher->name + 1, 1, "0123456789", 1);
	write(1, " ", 1);
	if (action == E_ACT_FORK)
		write(1, "has taken a fork", 16);
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

void	lock_hand(t_philosopher *src, bool lock)
{
	if (lock == true && src->name % 2 == 0)
	{
		pthread_mutex_lock(src->hand_lock_l);
		pthread_mutex_lock(src->hand_lock_r);
	}
	if (lock == false && src->name % 2 == 0)
	{
		pthread_mutex_unlock(src->hand_lock_l);
		pthread_mutex_unlock(src->hand_lock_r);
	}
	if (lock == true && src->name % 2 == 1)
	{
		pthread_mutex_lock(src->hand_lock_r);
		pthread_mutex_lock(src->hand_lock_l);
	}
	if (lock == false && src->name % 2 == 1)
	{
		pthread_mutex_unlock(src->hand_lock_r);
		pthread_mutex_unlock(src->hand_lock_l);
	}
}

bool	f_is_loop(t_philosopher *src)
{
	if (src == NULL)
		return (false);
	if (((0 < src->time_to_live && src->current_time < src->time_to_live)
		|| (src->time_to_live == 0)) && src->is_loop != NULL && *src->is_loop == true)
		return (true);
	return (false);
}

void	*philosopher_action(void *arg)
{
	t_philosopher	*philosopher;
	clock_t current;

	if (arg == NULL)
		return (NULL);
	philosopher = (t_philosopher *)arg;
	philosopher->prev_eat = clock();
	while (f_is_loop(philosopher) == true)
	{
		lock_hand(philosopher, true);
		usleep(philosopher->time_to_eat);
		current = clock();
		if (current - philosopher->prev_eat < philosopher->time_to_die)
			write_philosopher_biography(philosopher, E_ACT_EAT);
		else
		{
			write_philosopher_biography(philosopher, E_ACT_DIE);
			if (philosopher->is_loop != NULL)
				*(philosopher->is_loop) = false;
		}
		philosopher->prev_eat = clock();
		lock_hand(philosopher, false);
		philosopher->current_time += 1;
		if (f_is_loop(philosopher) == true)
		{
			usleep(philosopher->time_to_sleep);
			write_philosopher_biography(philosopher, E_ACT_SLEEP);
		}
	}
	return (NULL);
}
