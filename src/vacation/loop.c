#include "vacation.h"

void	write_travel_log(const t_visitor *src, int fd)
{
	if (src == NULL)
		return ;
	write(fd, "::: ", 4);
	ft_putnbr_fd(src->name, fd, "0123456789", 2);
	write(fd, " live at ", 9);
	ft_putnbr_fd(src->current_address, fd, "0123456789", 2);
	write(fd, " (", 2);
	ft_putnbr_fd(src->record_time, fd, "0123456789", 1);
	write(fd, "-th day)\n", 10);
}

size_t	travel_next_home(const t_visitor *src)
{
	size_t	next_address;

	if (src == NULL)
		return (0);
	next_address = rand() % src->length;
	return (next_address);
}

void	*vacation_action(void *arg)
{
	t_visitor	*dst;

	dst = arg;
	if (arg == NULL)
		return (NULL);
	while (dst->record_time < dst->max_record_time)
	{
		usleep(dst->car_speed);
		if (dst->clients != NULL)
			sem_wait(dst->clients);
		dst->current_address = travel_next_home(dst);
		write_travel_log(dst, 1);
		if (dst->clients != NULL)
			sem_post(dst->clients);
		dst->record_time += 1;
	}
	return (NULL);
}

/*
To Do Now
1.	Watching more PThread video.
*/
