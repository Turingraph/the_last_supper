#include "philosopher.h"

void	write_philosopher_biography(
	const t_philosopher *philosopher, bool is_eat)
{
	if (philosopher == NULL)
		return ;
	pthread_mutex_lock(philosopher->mutex);
	ft_putnbr_fd(philosopher->name, 1, "0123456789", 1);
	write(1, " ", 1);
	if (is_eat == true)
		write(1, "eat", 3);
	else
		write(1, "think", 5);
	write(1, " at ", 4);
	ft_putnbr_fd(philosopher->current_time, 1, "0123456789", 1);
	write(1, " day\n", 5);
	pthread_mutex_unlock(philosopher->mutex);
}

void	*philosopher_right_action(void *arg)
{
	t_philosopher	*philosopher;

	if (arg == NULL)
		return (NULL);
	philosopher = (t_philosopher *)arg;
	while (philosopher->current_time < philosopher->time_to_live)
	{
		pthread_mutex_lock(philosopher->hand_lock_l);
		pthread_mutex_lock(philosopher->hand_lock_r);
		usleep(philosopher->time_to_eat);
		write_philosopher_biography(philosopher, true);
		pthread_mutex_unlock(philosopher->hand_lock_l);
		pthread_mutex_unlock(philosopher->hand_lock_r);
		philosopher->current_time += 1;
		if (philosopher->current_time < philosopher->time_to_live)
		{
			usleep(philosopher->time_to_sleep);
			write_philosopher_biography(philosopher, false);
		}
	}
	return (NULL);
}

void	*philosopher_left_action(void *arg)
{
	t_philosopher	*philosopher;

	if (arg == NULL)
		return (NULL);
	philosopher = (t_philosopher *)arg;
	while (philosopher->current_time < philosopher->time_to_live)
	{
		pthread_mutex_lock(philosopher->hand_lock_r);
		pthread_mutex_lock(philosopher->hand_lock_l);
		usleep(philosopher->time_to_eat);
		write_philosopher_biography(philosopher, true);
		pthread_mutex_unlock(philosopher->hand_lock_r);
		pthread_mutex_unlock(philosopher->hand_lock_l);
		philosopher->current_time += 1;
		if (philosopher->current_time < philosopher->time_to_live)
		{
			usleep(philosopher->time_to_sleep);
			write_philosopher_biography(philosopher, false);
		}
	}
	return (NULL);
}
