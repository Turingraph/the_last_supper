# include "philo/philosopher.h"

static void	third_main(size_t length, pthread_t *thread,
	t_philosopher *philosophers, bool *is_loop)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		philosophers[i].is_loop = is_loop;
		pthread_create(thread + i, NULL,
			philosopher_action, (void*)(philosophers + i));
		i += 1;
	}
	i = 0;
	while (i < length)
	{
		pthread_join(thread[i], NULL);
		i += 1;
	}
}

static void	second_main(t_philosopher arg,
	pthread_mutex_t *sem_arr, pthread_mutex_t *mutex, pthread_t *thread)
{
	t_philosopher	*philosophers;
	size_t			i;
	bool			is_loop;

	philosophers = init_philosopher_arr(arg.length, sem_arr, mutex);
	update_philosophers(philosophers, arg.time_to_live, E_TIMETOLIVE, arg.length);
	update_philosophers(philosophers, arg.time_to_eat, E_TIMETOEAT, arg.length);
	update_philosophers(philosophers, arg.time_to_die, E_TIMETODIE, arg.length);
	update_philosophers(philosophers, arg.time_to_sleep, E_TIMETOSLEEP, arg.length);
	if (philosophers == NULL)
		return ;
	is_loop = true;
	third_main(arg.length, thread, philosophers, &is_loop);
	i = 0;
	while (i < arg.length)
	{
		pthread_mutex_destroy(sem_arr + i);
		i += 1;
	}
	free(philosophers);
}

static void fourth_main(t_philosopher arg)
{
	pthread_mutex_t	*sem_arr;
	pthread_mutex_t	mutex;
	pthread_t		*thread;

	sem_arr = init_multisems(arg.length);
	thread = malloc_talk(sizeof(pthread_t) * arg.length, "philosophers (pthread)\n");
	if (sem_arr == NULL || thread == NULL)
	{
		free(sem_arr);
		free(thread);
		return ;
	}
	pthread_mutex_init(&mutex, NULL);
	second_main(arg, sem_arr, &mutex, thread);
	free(sem_arr);
	free(thread);
	pthread_mutex_destroy(&mutex);
}

int	main(int len, char **str)
{
	t_philosopher	arg;
	size_t	i;
	size_t	length;
	bool	is_int;

	if (len < 5)
		return (0);
	i = 1;
	while ((int)i < len && i < 6)
	{
		is_int = true;
		length = (size_t)f_abs(f_atoi(str[i], &is_int,
			"0123456789", knight_of_coin(str[i], ' ')));
		if (is_int == false || (i != 3 && length < 1))
			return (0);
		if (i == 1)
			arg = init_philosopher_unit(0, length, NULL, NULL);
		if (i == 2)
			arg.time_to_die = length;
		if (i == 3)
			arg.time_to_eat = length;
		if (i == 4)
			arg.time_to_sleep = length;
		if (i == 5)
			arg.time_to_live = length;
		i += 1;
	}
	if (arg.length < 2)
	{
		usleep(arg.time_to_die);
		clock_t current = clock();
		ft_putnbr_fd(current, 1, "0123456789", 1);
		write(1, " 1 die\n", 7);
	}
	else
		fourth_main(arg);
	return (0);
}

/*
valgrind --leak-check=full --show-leak-kinds=all ./out/main.out 10 10000 700 2400 6

pc@pc-System-Product-Name:~/Desktop/love_the_knowledge/philo$ valgrind --leak-check=full --show-leak-kinds=all ./out/main.out 10 10000 700 2400 6
==440480== Memcheck, a memory error detector
==440480== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==440480== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==440480== Command: ./out/main.out 10 10000 700 2400 6
==440480== 
907264 6 is eating(0)
911799 8 is eating(0)
911841 2 is eating(0)
915007 4 die(0)
919694 9 die(0)
919744 7 die(0)
928869 1 die(0)
928918 5 die(0)
928968 3 die(0)
929152 6 is sleeping(1)
929187 8 is sleeping(1)
929237 2 is sleeping(1)
933257 10 die(0)
==440480== 
==440480== HEAP SUMMARY:
==440480==     in use at exit: 0 bytes in 0 blocks
==440480==   total heap usage: 13 allocs, 13 frees, 4,240 bytes allocated
==440480== 
==440480== All heap blocks were freed -- no leaks are possible
==440480== 
==440480== For lists of detected and suppressed errors, rerun with: -s
==440480== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
pc@pc-System-Product-Name:~/Desktop/love_the_knowledge/philo$ 
*/