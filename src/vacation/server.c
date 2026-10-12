#include "vacation.h"

void	*traveloka_action(void *arg)
{
	static size_t	record_time = 0;
	static size_t	client_count = 0;
	t_traveloka	*dst;

	dst = arg;
	if (dst == NULL || dst->clients == NULL || dst->server == NULL)
		return (NULL);
	while (record_time < dst->max_record_time)
	{
		sem_wait(dst->clients);
		client_count += 1;
		if (client_count == dst->length)
		{
			record_time += 1;
			// sem_post(dst->server);
		}
	}
	return (NULL);
}
