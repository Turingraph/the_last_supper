#include "vacation.h"

t_home_arr	init_homes(size_t length)
{
	t_home_arr	dst;
	t_home	*arr;
	size_t	i;

	arr = malloc_talk(sizeof(t_visitor) * length, "vacation (args)\n");
	if (arr == NULL)
	{
		dst.length = 0;
		dst.arr = NULL;
		dst.next_loop = true;
		return (dst);
	}
	i = 0;
	while (i < length)
	{
		arr[i].visitor = i;
		arr[i].prev_visitor = i;
		arr[i].is_booked = false;
		i += 1;
	}
	dst.length = length;
	dst.arr = arr;
	dst.next_loop = true;
	return (dst);
}

t_visitor	*init_visitors(size_t *arg_length, int len)
{
	size_t	i;
	t_visitor	*args;
	t_home_arr	arr;

	arr = init_homes(arg_length[0]);
	if (arr.length == 0)
		return (NULL);
	args = malloc_talk(sizeof(t_visitor) * arg_length[0], "vacation (args)\n");
	if (args == NULL)
	{
		free(arr.arr);
		free(arg_length);
		return (NULL);
	}
	i = 0;
	while (i < arg_length[0])
	{
		args[i].record_time = 0;
		args[i].max_record_time = arg_length[1];
		args[i].home_arr = arr;
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
	while (i < arg[0].home_arr.length)
	{
		arg[i].mutex = mutex;
		arg[i].clients = clients;
		arg[i].server = server;
		i += 1;
	}
}
