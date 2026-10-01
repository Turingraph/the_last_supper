#include "roulette.h"

void	write_log(const t_person *src, int fd)
{
	if (src == NULL)
		return ;
	write(fd, ">>> ", 4);
	ft_putnbr_fd(src->name, fd, "0123456789", 1);
	write(fd, " is ", 4);
	ft_putnbr_fd(src->age, fd, "0123456789", 1);
	write(fd, " year old today.", 17);
	if (src->alive == false)
		write(fd, " He die.", 8);
	write(fd, "\n", 1);
}

void	*roulette_action(void *arg)
{
	t_arg		*src;

	src = arg;
	if (arg == NULL || src->all_bullet == 0)
		return (NULL);
	src->bullet = rand();
	if (src->person[src->queue].name == src->bullet % src->all_bullet)
		src->person[src->queue].alive = false;
	write_log(&(src->person[src->queue]), 1);
	src->person[src->queue].age += 1;
	return (NULL);
}

// all_bullet
// init_bullet

int	main(int len, char **str)
{
	size_t		all_bullet;
	size_t		bullet;
	size_t		temp;
	t_arg		arg;
	t_person	*person;
	bool		is_int = true;
	bool		is_int2 = true;
	size_t		i;

	if (len < 3)
	{
		write(1, "Input is invalid.\n", 18);
		return (0);
	}
	all_bullet = (size_t)f_abs(f_atoi(str[1], &is_int, "0123456789", knight_of_coin(str[1], ' ')));
	bullet = (size_t)f_abs(f_atoi(str[2], &is_int2, "0123456789", knight_of_coin(str[2], ' ')));
	if (is_int == false || is_int2 == false || all_bullet < 3 || bullet < 3)
	{
		write(1, "Input is invalid.\n", 18);
		return (0);
	}
	if (all_bullet < bullet)
	{
		temp = bullet;
		bullet = all_bullet;
		all_bullet = temp;
	}

	person = malloc_talk(sizeof(t_person) * all_bullet, "roulette\n");
	if (person == NULL)
		return (0);
	i = 0;
	while (i < all_bullet)
	{
		person[i].name = i;
		person[i].alive = true;
		person[i].age = 0;
		i += 1;
	}
	arg.person = person;
	arg.all_bullet = all_bullet;
	arg.bullet = bullet;
	arg.queue = 0;
	while (arg.person[arg.queue].alive == true)
	{
		roulette_action((void *)&arg);
		if (arg.person[arg.queue].alive == true)
		{
			arg.queue += 1;
			arg.queue %= arg.all_bullet;
		}
	}
	free(person);
	return (0);
}

/*
valgrind --leak-check=full --show-leak-kinds=all ./unit_test/out/roulette/main.out
*/
