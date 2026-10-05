#include "vacation.h"

bool	is_arg_valid(const t_visitor *src)
{
	if (src == NULL
		|| src->home_arr.arr == NULL || src->home_arr.length < 1)
		return (false);
	return (true);
}

void	write_travel_log(const t_visitor *src, int fd)
{
	if (is_arg_valid(src) == false)
		return ;
	write(fd, "::: ", 4);
	ft_putnbr_fd(src->name, fd, "0123456789", 2);
	write(fd, " live at ", 9);
	ft_putnbr_fd(src->current_address, fd, "0123456789", 2);
	write(fd, " (", 2);
	ft_putnbr_fd(src->record_time, fd, "0123456789", 1);
	write(fd, "-th day, ", 9);
	ft_putnbr_fd(src->name, fd, "0123456789", 2);
	write(1, " != ", 4);
	ft_putnbr_fd(src->home_arr.arr[src->current_address].prev_visitor, fd, "0123456789", 2);
	write(fd, ")\n", 2);
}

bool	is_valid_home(const t_home_arr *home, size_t next_address, size_t visitor, size_t current_address)
{
	if (home == NULL
		|| home->arr[next_address].prev_visitor == (int)visitor
		|| home->arr[next_address].is_booked == true
		|| next_address == current_address)
		return (false);
	return (true);
}

size_t	travel_next_home(const t_visitor *src)
{
	size_t	next_address;

	if (is_arg_valid(src) == false)
		return (0);
	next_address = rand() % src->home_arr.length;
	while (is_valid_home(&src->home_arr, next_address, src->name, src->current_address) == false)
		next_address = rand() % src->home_arr.length;
	return (next_address);
}

bool	is_all_home_book(t_home_arr *dst)
{
	size_t	i;

	if (dst == NULL || dst->length < 1)
		return (false);
	i = 0;
	while (i < dst->length)
	{
		if (dst->arr[i].is_booked == false)
			return (false);
		i += 1;
	}
	return (true);
}

void	reset_home(t_home_arr *dst)
{
	size_t	i;

	if (dst == NULL || dst->length < 1)
		return ;
	i = 0;
	while (i < dst->length)
	{
		dst->arr[i].is_booked = false;
		i += 1;
	}
}

void	*vacation_action(void *arg)
{
	t_visitor	*dst;

	dst = arg;
	if (is_arg_valid(dst) == false)
		return (NULL);
	while (dst->record_time < dst->max_record_time)
	{
		usleep(dst->car_speed);
		dst->home_arr.arr[dst->current_address].prev_visitor = dst->name;
		if (dst->clients != NULL)
			sem_wait(dst->clients);
		dst->current_address = travel_next_home(dst);
		dst->home_arr.arr[dst->current_address].is_booked = true;
		dst->home_arr.arr[dst->current_address].visitor = dst->name;
		write_travel_log(dst, 1);
		if (dst->clients != NULL)
			sem_post(dst->clients);
		reset_home(&dst->home_arr);
		dst->record_time += 1;
	}
	return (NULL);
}

/*
To Do Now
1.	Watching more PThread video.
*/
