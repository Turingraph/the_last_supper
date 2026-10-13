# include "../../src/philosopher/philosopher.h"

static void	third_main(size_t length, pthread_t *thread, t_philosopher *philosophers)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (i % 2 == 0)
			pthread_create(thread + i, NULL, philosopher_right_action, (void*)(philosophers + i));
		else
			pthread_create(thread + i, NULL, philosopher_left_action, (void*)(philosophers + i));
		i += 1;
	}
	i = 0;
	while (i < length)
	{
		pthread_join(thread[i], NULL);
		i += 1;
	}
}

static void	second_main(size_t length,
	sem_t *sem_arr, pthread_mutex_t *mutex, pthread_t *thread)
{
	t_philosopher	*philosophers;
	size_t			i;

	philosophers = init_philosopher_arr(length, 10, sem_arr, mutex);
	if (philosophers == NULL)
		return ;
	third_main(length, thread, philosophers);
	i = 0;
	while (i < length)
	{
		sem_destroy(sem_arr + i);
		i += 1;
	}
	free(philosophers);
}

static void fourth_main(size_t length)
{
	sem_t			*sem_arr;
	pthread_mutex_t	mutex;
	pthread_t		*thread;

	sem_arr = init_multisems(length);
	thread = malloc_talk(sizeof(pthread_t) * length, "philosophers (pthread)\n");
	if (sem_arr == NULL || thread == NULL)
	{
		free(sem_arr);
		free(thread);
		return ;
	}
	pthread_mutex_init(&mutex, NULL);
	second_main(length, sem_arr, &mutex, thread);
	free(sem_arr);
	free(thread);
	pthread_mutex_destroy(&mutex);
}

int	main(int len, char **str)
{
	size_t	length;
	bool	is_int;

	if (len < 2)
		return (0);
	is_int = true;
	length = (size_t)f_abs(f_atoi(str[1], &is_int,
		"0123456789", knight_of_coin(str[1], ' ')));
	if (is_int == false || length < 2)
		return (0);
	fourth_main(length);
	return (0);
}

/*
valgrind --leak-check=full --show-leak-kinds=all ./unit_test/out/philosopher/main.out
*/