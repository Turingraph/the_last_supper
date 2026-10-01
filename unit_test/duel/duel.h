#ifndef DUEL_H
# define DUEL_H

# include "../../src/utils/utils.h"
# include <pthread.h>

typedef enum t_team
{
	TEAM_A,
	TEAM_B,
}	t_team;

typedef struct t_competitor
{
	size_t	name;
	bool	alive;
	size_t	kill_counts;
}	t_competitor;

typedef struct t_duel
{
	t_competitor	*competitor;
	size_t			times;
	size_t			length;
	size_t			queue_a;
	size_t			queue_b;
	bool			battle;
	pthread_mutex_t *mutex;
}	t_duel;

typedef struct t_arg
{
	size_t	queue;
	t_team	team;
	t_duel	*duel;
}	t_arg;

#endif
