#include "duel.h"

bool	is_arg_valid(const t_arg *src)
{
	if (src == NULL || src->duel == NULL
		|| src->duel->battle == false
		|| src->duel->length < 2 || src->duel->competitor == NULL)
		return (false);
	return (true);
}

int	*rand_int_arr(size_t length)
{
	size_t	i;
	int		*dst;

	dst = malloc_talk(sizeof(int) * length, "rand_int_arr\n");
	if (dst == NULL)
		return (NULL);
	srand(time(NULL));
	i = 0;
	while (i < length)
	{
		dst[i] = rand() % 83742;
		i += 1;
	}
	return (dst);
}

bool	is_battle_start(t_competitor *arr, size_t length)
{
	size_t	i;
	size_t	j;

	if (length < 1 || arr == NULL)
		return (false);
	j = 0;
	i = 0;
	while (i < length)
	{
		if (arr[i].alive == true)
			j += 1;
		if (j >= 2)
			return (true);
		i += 1;
	}
	return (false);
}

size_t	return_unique_index(t_competitor *arr, size_t a, size_t b, size_t length)
{
	size_t	i;

	if (arr == NULL || length < 1 || a >= length)
		return (0);
	i = 0;
	while ((a == b || arr[a].alive == false) && i < length)
	{
		a += 1;
		a %= length;
		i += 1;
	}
	return (a);
}

void	write_criminal_record(size_t bad_guy, size_t victim, int fd, t_team team)
{
	char	a;
	char	b;

	a = 'A';
	b = 'B';
	if (team == TEAM_B)
	{
		a = 'B';
		b = 'A';
	}
	write(fd, "::: ", 4);
	write(fd, &a, 1);
	ft_putnbr_fd(bad_guy, fd, "0123456789", 1);
	write(fd, " killed ", 8);
	write(fd, &b, 1);
	ft_putnbr_fd(victim, fd, "0123456789", 1);
	write(fd, "\n", 1);
}

void	*duel_action(void *arg)
{
	t_arg	*dst;
	t_duel	*duel;
	size_t	queue_b;
	int		*arr;
	int		*arr2;

	dst = arg;
	if (is_arg_valid(dst) == false)
		return (NULL);
	duel = dst->duel;
	while (duel->battle == true)
	{
		pthread_mutex_lock(duel->mutex);
		if (dst->team == TEAM_A)
		{
			duel->queue_a = dst->queue;
			queue_b = duel->queue_b;
		}
		else
		{
			duel->queue_b = dst->queue;
			queue_b = duel->queue_a;
		}
		duel->battle = is_battle_start(dst->duel->competitor, duel->length);
		if (duel->battle == false)
		{
			pthread_mutex_unlock(duel->mutex);
			return (NULL);
		}
		dst->queue = return_unique_index(dst->duel->competitor,
			dst->queue, queue_b, duel->length);
		queue_b = return_unique_index(dst->duel->competitor,
			queue_b, dst->queue, duel->length);
		pthread_mutex_unlock(duel->mutex);
		arr = rand_int_arr(duel->times);
		arr2 = merge_sort(arr, duel->times);
		free(arr);
		free(arr2);
		pthread_mutex_lock(duel->mutex);
		if (duel->competitor[dst->queue].alive == true && duel->competitor[queue_b].alive == true)
		{
			duel->competitor[dst->queue].kill_counts += 1;
			duel->competitor[queue_b].alive = false;
			write_criminal_record(dst->queue, queue_b, 1, dst->team);
			dst->queue += 1;
			queue_b += 2;
			dst->queue %= duel->length;
		}
		pthread_mutex_unlock(duel->mutex);
	}
	return (NULL);
}

int	main(int len, char **str)
{
	size_t		length;
	size_t		time;
	bool		is_int = true;
	bool		is_int2 = true;

	if (len < 3)
	{
		write(1, "Input is invalid.\n", 18);
		return (0);
	}
	length = (size_t)f_abs(f_atoi(str[2], &is_int, "0123456789", knight_of_coin(str[2], ' ')));
	time = (size_t)f_abs(f_atoi(str[1], &is_int2, "0123456789", knight_of_coin(str[1], ' ')));
	if (is_int == false || length < 3 || is_int2 == false || time < 3)
	{
		write(1, "Input is invalid.\n", 18);
		return (0);
	}

	size_t			i;
	pthread_mutex_t mutex;
	t_competitor	*competitor;
	t_duel			duel;

	competitor = malloc_talk(sizeof(t_competitor) * length, "duel\n");
	if (competitor == NULL)
		return (0);
	i = 0;
	while (i < length)
	{
		competitor[i].name = i;
		competitor[i].alive = true;
		competitor[i].kill_counts = 0;
		i += 1;
	}
	duel.competitor = competitor;
	duel.times = time;
	duel.length = length;
	duel.queue_a = 0;
	duel.queue_b = length - 1;
	duel.battle = true;
	pthread_mutex_init(&mutex, NULL);
	duel.mutex = &mutex;

	pthread_t	thread_a;
	pthread_t	thread_b;
	t_arg		arg_a;
	t_arg		arg_b;

	arg_a.duel = &duel;
	arg_b.duel = &duel;
	arg_a.team = TEAM_A;
	arg_b.team = TEAM_B;
	arg_a.queue = 0;
	arg_b.queue = length - 1;

	if (pthread_create(&thread_a, NULL, duel_action, (void*)&arg_a) != 0
		|| pthread_create(&thread_b, NULL, duel_action, (void*)&arg_b) != 0)
	{
		free(competitor);
		pthread_mutex_destroy(&mutex);
		return (0);
	}
	if (rand() % 2 == 0)
	{
		pthread_join(thread_a, NULL);
		pthread_join(thread_b, NULL);
	}
	else
	{
		pthread_join(thread_b, NULL);
		pthread_join(thread_a, NULL);
	}
	i = 0;
	while (i < length)
	{
		if (competitor[i].alive == true)
		{
			write(1, "The survival is ", 16);
			ft_putnbr_fd(competitor[i].name, 1, "0123456789", 1);
			write(1, ". They also kills ", 18);
			ft_putnbr_fd(competitor[i].kill_counts, 1, "0123456789", 1);
			write(1, " victims", 8);
			write(1, ".\n", 2);
		}
		i += 1;
	}
	free(competitor);
	pthread_mutex_destroy(&mutex);
	return (0);
}

/*
valgrind --leak-check=full --show-leak-kinds=all ./unit_test/out/duel/main.out 1000 100
*/
