# include "../../src/philosopher/philosopher.h"

int	main(int len, char **str)
{
	size_t	length;
	bool	is_int;
	size_t	i;
	t_philosopher	*philosophers;

	if (len < 2)
		return (0);
	is_int = true;
	length = (size_t)f_abs(f_atoi(str[1], &is_int,
		"0123456789", knight_of_coin(str[1], ' ')));
	if (is_int == false || length < 1)
		return (0);
	sem_t	*sem_arr = init_multisems(length);
	pthread_mutex_t mutex;
	t_fork	*forks;
	pthread_mutex_init(&mutex, NULL);
	philosophers = init_philosopher_arr(length, 100, sem_arr, &mutex);
	forks = init_fork_arr(length, sem_arr, &mutex);
	i = 0;
	while (i < length)
	{
		sem_destroy(sem_arr + i);
		i += 1;
	}
	free(forks);
	free(philosophers);
	free(sem_arr);
	pthread_mutex_destroy(&mutex);
	return (0);
}

/*
valgrind --leak-check=full --show-leak-kinds=all ./unit_test/out/philosopher/main.out
*/