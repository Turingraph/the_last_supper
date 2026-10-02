#ifndef VACATION_H
# define VACATION_H

# include "../../src/utils/utils.h"
# include <pthread.h>

typedef struct t_home
{
	int		visitor;
	int		traveler;
}	t_home;

typedef struct t_arg
{
	size_t		record_time;
	size_t		max_record_time;
	t_home		*homes;
	size_t		length;
	size_t		name;
	size_t		current_address;
	size_t		car_speed;
}	t_arg;

#endif
