#include "vacation.h"

void	reset_home(t_home_arr *dst)
{
	size_t	i;

	if (dst == NULL || dst->length < 1)
		return ;
	i = 0;
	while (i < dst->length)
	{
		dst->arr[i].is_booked = false;
		i += 1;
	}
}

void	*traveloka_action(void *arg)
{
	static size_t	record_time = 0;
	static size_t	client_count = 0;
	t_traveloka	*dst;

	dst = arg;
	if (dst == NULL || dst->clients == NULL || dst->server == NULL
		|| dst->home_arr->arr == NULL || dst->home_arr->length < 1)
		return (NULL);
	while (record_time < dst->max_record_time)
	{
		sem_wait(dst->clients);
		client_count += 1;
		if (client_count == dst->home_arr->length)
		{
			reset_home(dst->home_arr);
			record_time += 1;
			sem_post(dst->server);
		}
	}
	return (NULL);
}
