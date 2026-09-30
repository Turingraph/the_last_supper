#ifndef ROULETTE_H
# define ROULETTE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct t_roulette
{
	size_t	name;
	bool	alive;
	int		last_time;
	size_t	age;
}	t_roulette;

#endif
