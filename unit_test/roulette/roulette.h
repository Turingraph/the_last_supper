#ifndef ROULETTE_H
# define ROULETTE_H

# include "../../src/utils/utils.h"

typedef struct t_competitor
{
	size_t	name;
	bool	alive;
	size_t	age;
}	t_competitor;

typedef struct t_arg
{
	t_competitor	*person;
	size_t		bullet;
	size_t		all_bullet;
	size_t		queue;
}	t_arg;

#endif
