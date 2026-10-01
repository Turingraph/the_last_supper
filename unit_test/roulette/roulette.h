#ifndef ROULETTE_H
# define ROULETTE_H

# include "../../src/utils/utils.h"

typedef struct t_person
{
	size_t	name;
	bool	alive;
	size_t	age;
}	t_person;

typedef struct t_arg
{
	t_person	*person;
	size_t		bullet;
	size_t		all_bullet;
	size_t		queue;
}	t_arg;

#endif
