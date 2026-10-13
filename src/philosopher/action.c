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
	ft_putnbr_fd(philosopher->day, 1, "0123456789", 1);
	write(1, " day\n", 5);
	pthread_mutex_unlock(philosopher->mutex);
}

void	*philosopher_right_action(void *arg)
{
	t_philosopher	*philosopher;

	if (arg == NULL)
		return (NULL);
	philosopher = (t_philosopher *)arg;
	while (philosopher->day < philosopher->max_day)
	{
		sem_wait(philosopher->hand_lock_l);
		sem_wait(philosopher->hand_lock_r);
		usleep(philosopher->eat_time);
		write_philosopher_biography(philosopher, true);
		sem_post(philosopher->hand_lock_l);
		sem_post(philosopher->hand_lock_r);
		usleep(philosopher->think_time);
		write_philosopher_biography(philosopher, false);
		philosopher->day += 1;
	}
	return (NULL);
}

void	*philosopher_left_action(void *arg)
{
	t_philosopher	*philosopher;

	if (arg == NULL)
		return (NULL);
	philosopher = (t_philosopher *)arg;
	while (philosopher->day < philosopher->max_day)
	{
		sem_wait(philosopher->hand_lock_r);
		sem_wait(philosopher->hand_lock_l);
		usleep(philosopher->eat_time);
		write_philosopher_biography(philosopher, true);
		sem_post(philosopher->hand_lock_r);
		sem_post(philosopher->hand_lock_l);
		usleep(philosopher->think_time);
		write_philosopher_biography(philosopher, false);
		philosopher->day += 1;
	}
	return (NULL);
}
