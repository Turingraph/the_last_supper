# include "../../src/vacation/vacation.h"

int	main(int len, char **str)
{
	size_t	*arg_length;
	bool	is_int;
	size_t	i;

	if (len < 4)
	{
		write(1, "Input is invalid.\n", 18);
		return (0);
	}
	arg_length = malloc_talk(sizeof(size_t) * (len - 1), "vacation\n");
	if (arg_length == NULL)
		return (0);
	i = 1;
	while ((int)i < len)
	{
		is_int = true;
		arg_length[i - 1] = (size_t)f_abs(f_atoi(str[i], &is_int, "0123456789", knight_of_coin(str[i], ' ')));
		if (is_int == false || (arg_length[i - 1] < 2 && i != 2) || (arg_length[i - 1] < 1 && i == 2))
		{
			write(1, "input is invalid.\n", 18);
			free(arg_length);
			return (0);
		}
		i += 1;
	}

	pthread_t	*thread = malloc_talk(sizeof(pthread_t) * (arg_length[0] + 1), "vacation (pthread)\n");
	t_visitor	*args = init_visitors(arg_length, len);
	pthread_mutex_t mutex;
	sem_t clients;

	pthread_mutex_init(&mutex, NULL);
	sem_init(&clients, 0, 1);
	init_visitor_mutex(args, &mutex, &clients, NULL);
	i = 0;
	while (i < arg_length[0])
	{
		pthread_create(thread + i, NULL, vacation_action, (void*)(args + i));
		i += 1;
	}
	i = 0;
	while (i < arg_length[0])
	{
		pthread_join(thread[i], NULL);
		i += 1;
	}
	free(thread);
	free(args);
	pthread_mutex_destroy(&mutex);
	free(arg_length);
	sem_destroy(&clients);
	return (0);
}

/*
valgrind --leak-check=full --show-leak-kinds=all ./unit_test/out/vacation/main.out 5 10 300 310 333

*/
