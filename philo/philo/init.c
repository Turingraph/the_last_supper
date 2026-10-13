#include "philosopher.h"

t_philosopher	init_philosopher_unit(size_t i,
	size_t length,
	pthread_mutex_t *hand_lock,
	pthread_mutex_t *mutex)
{
	t_philosopher	dst;

	dst.name = i;
	dst.length = length;
	dst.is_pick_left = false;
	dst.is_pick_right = false;
	dst.current_time = 0;
	dst.time_to_live = 100;
	dst.time_to_eat = 100;
	dst.time_to_sleep = 100;
	dst.prev_eat = 0;
	dst.is_loop = NULL;
	dst.hand_lock_l = hand_lock + i;
	dst.hand_lock_r = hand_lock + (i + 1) % length;
	dst.mutex = mutex;
	return (dst);
}

t_philosopher	*init_philosopher_arr(size_t length,
	pthread_mutex_t *hand_lock,
	pthread_mutex_t *mutex)
{
	t_philosopher	*dst;
	size_t	i;

	if (length < 2 || hand_lock == NULL)
		return (NULL);
	dst = malloc_talk(sizeof(t_philosopher) * length, "philosopher\n");
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dst[i] = init_philosopher_unit(i, length, hand_lock, mutex);
		i += 1;
	}
	return (dst);
}

void	update_philosophers(t_philosopher *dst,
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
