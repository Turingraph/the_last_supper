#include "vacation.h"

t_visitor	*init_visitors(size_t *arg_length, int len)
{
	size_t	i;
	t_visitor	*args;

	args = malloc_talk(sizeof(t_visitor) * arg_length[0], "vacation (args)\n");
	if (args == NULL)
		return (NULL);
	i = 0;
	while (i < arg_length[0])
	{
		args[i].record_time = 0;
		args[i].max_record_time = arg_length[1];
		args[i].length = arg_length[0];
		args[i].name = i;
		args[i].current_address = i;
		args[i].car_speed = arg_length[2];
		args[i].mutex = NULL;
		args[i].clients = NULL;
		args[i].server = NULL;
		i += 1;
	}
	i = 3;
	while ((int)i < len - 1 && (int)i - 2 < (int)arg_length[0])
	{
		args[i - 2].car_speed = arg_length[i];
		i += 1;
	}
	return (args);
}


void	init_visitor_mutex(t_visitor *arg, pthread_mutex_t *mutex, sem_t *clients, sem_t *server)
{
	size_t	i;

	i = 0;
	while (i < arg[0].length)
	{
		arg[i].mutex = mutex;
		arg[i].clients = clients;
		arg[i].server = server;
		i += 1;
	}
}
