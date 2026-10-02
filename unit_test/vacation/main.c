#include "vacation.h"

bool	is_arg_valid(const t_arg *src)
{
	if (src == NULL || src->homes == NULL || src->length < 1)
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

void	write_travel_log(const t_arg *src, int fd)
{
	if (is_arg_valid(src) == false)
		return ;
	write(fd, "::: ", 4);
	ft_putnbr_fd(src->name, fd, "0123456789", 1);
	write(fd, " live at ", 9);
	ft_putnbr_fd(src->current_address, fd, "0123456789", 1);
	write(fd, " (", 2);
	ft_putnbr_fd(src->car_speed, fd, "0123456789", 1);
	write(fd, ")\n", 2);
}

t_home	*init_homes(size_t length)
{
	t_home	*homes;
	size_t	i;

	homes = malloc_talk(sizeof(t_arg) * length, "vacation (args)\n");
	if (homes == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		homes[i].visitor = i;
		homes[i].traveler = -1;
		i += 1;
	}
	return (homes);
}

t_arg	*init_args(size_t *arg_length, int len)
{
	size_t	i;
	t_arg	*args;
	t_home	*homes;

	homes = init_homes(arg_length[0]);
	if (homes == NULL)
		return (NULL);
	args = malloc_talk(sizeof(t_arg) * arg_length[0], "vacation (args)\n");
	if (args == NULL)
	{
		free(homes);
		free(arg_length);
		return (NULL);
	}
	i = 0;
	while (i < arg_length[0])
	{
		args[i].record_time = 0;
		args[i].max_record_time = arg_length[1];
		args[i].homes = homes;
		args[i].length = arg_length[0];
		args[i].name = i;
		args[i].current_address = i;
		args[i].car_speed = arg_length[2];
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
		if (is_int == false || arg_length[i - 1] < 2)
		{
			write(1, "input is invalid.\n", 18);
			free(arg_length);
			return (0);
		}
		i += 1;
	}

	t_arg	*args = init_args(arg_length, len);

	i = 0;
	while (i < arg_length[0])
	{
		write_travel_log(args + i, 1);
		i += 1;
	}
	free(arg_length);
	free(args->homes);
	free(args);
}

/*
valgrind --leak-check=full --show-leak-kinds=all ./unit_test/out/vacation/main.out 10 20 300 310 333

300
310
333
*/
