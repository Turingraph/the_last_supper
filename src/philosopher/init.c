#include "philosopher.h"

t_philosopher	*init_philosopher_arr(size_t length,
	size_t max_day,
	sem_t *hand_lock,
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
		dst[i].name = i;
		dst[i].length = length;
		dst[i].is_pick_left = false;
		dst[i].is_pick_right = false;
		dst[i].day = 0;
		dst[i].max_day = max_day;
		dst[i].eat_time = 100;
		dst[i].think_time = 100;
		dst[i].hand_lock_l = hand_lock + i;
		dst[i].hand_lock_r = hand_lock + (i + 1) % length;
		dst[i].mutex = mutex;
		i += 1;
	}
	return (dst);
}

sem_t	*init_multisems(size_t length)
{
	sem_t	*dst;
	size_t	i;

	if (length < 1)
		return (NULL);
	dst = malloc_talk(sizeof(sem_t) * length, "init_sem\n");
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		sem_init(dst + i, 0, 1);
		i += 1;
	}
	return (dst);
}

t_fork	*init_fork_arr(size_t length,
	sem_t *hand_lock,
	pthread_mutex_t *mutex)
{
	t_fork	*dst;
	size_t	i;

	if (length < 2 || hand_lock == NULL)
		return (NULL);
	dst = malloc_talk(sizeof(t_fork) * length, "philosopher\n");
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dst[i].name = i;
		dst[i].length = length;
		dst[i].is_used = false;
		dst[i].hand_lock = hand_lock + i;
		dst[i].max_day = 2 * length;
		dst[i].day = 0;
		dst[i].mutex = mutex;
		i += 1;
	}
	return (dst);
}
