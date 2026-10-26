# include "philo/philo.h"

static void	third_main(size_t length, pthread_t *thread,
	t_philo *philos, bool *is_loop)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		philos[i].is_loop = is_loop;
		pthread_create(thread + i, NULL,
			philo_action, (void*)(philos + i));
		i += 1;
	}
	i = 0;
	while (i < length)
	{
		pthread_join(thread[i], NULL);
		i += 1;
	}
}

static void	second_main(t_philo arg,
	pthread_mutex_t *sem_arr, pthread_mutex_t *mutex, pthread_t *thread)
{
	t_philo	*philos;
	size_t			i;
	size_t			current_time;
	bool			is_loop;

	philos = init_philo_arr(arg.length, sem_arr, mutex);
	update_philos(philos, arg.time_to_live, E_TIMETOLIVE, arg.length);
	update_philos(philos, arg.time_to_eat, E_TIMETOEAT, arg.length);
	update_philos(philos, arg.time_to_die, E_TIMETODIE, arg.length);
	update_philos(philos, arg.time_to_sleep, E_TIMETOSLEEP, arg.length);
	if (philos == NULL)
		return ;
	i = 0;
	current_time = 0;
	while (i < arg.length)
	{
		philos[i].current_time = &current_time;
		i += 1;
	}
	is_loop = true;
	third_main(arg.length, thread, philos, &is_loop);
	i = 0;
	while (i < arg.length)
	{
		pthread_mutex_destroy(sem_arr + i);
		i += 1;
	}
	free(philos);
}

static void fourth_main(t_philo arg)
{
	pthread_mutex_t	*sem_arr;
	pthread_mutex_t	mutex;
	pthread_t		*thread;

	sem_arr = init_multisems(arg.length);
	thread = malloc_talk(sizeof(pthread_t) * arg.length, "philos (pthread)\n");
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
	t_philo	arg;
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
		if (is_int == false
			|| (i == 1 && (length == 0 || length > 200))
			|| ((i == 2 || i == 3 || i == 4) && length < 60))
			return (0);
		if (i == 1)
			arg = init_philo_unit(0, length, NULL, NULL);
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

*/

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

/*
Note
1.	Add fork message (after thinking when able to access fork).
2.	Think after sleep and before eating. Someone might think until they die from starvation.
3.	use tester and visualizer ( https://rom98759.github.io/philos-visualizer/ )
4.	A message announcing a philo’s death must be displayed within (don't have to be late than) 10 ms of
their actual death.
5.	Timestamps are not in ascending order.

// What it is doing and why doing it ?
// 
if (philo->fork_left < philo->fork_right)
	//...

Reference
*	https://github.com/TrailOshell/philo
*/

/*
OK: Test 1 800 200 200. The philosopher should not eat and should die.
KO: Test 5 800 200 200. No philosopher should die.
KO: Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
KO: Test 4 410 200 200. No philosopher should die.
KO: Test 4 310 200 100. One philosopher should die.
Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, and so forth.
*/
