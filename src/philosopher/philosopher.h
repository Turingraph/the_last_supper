#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "../utils/utils.h"
# include <pthread.h>
# include <semaphore.h>

typedef struct t_philosopher
{
	size_t	name;
	size_t	length;
	bool	is_pick_left;
	bool	is_pick_right;
	size_t	eat_time;
	// size_t	starve_time;
	size_t	day;
	size_t	max_day;
	size_t	think_time;
	sem_t *hand_lock_l;
	sem_t *hand_lock_r;
	pthread_mutex_t	*mutex;
}	t_philosopher;

// action.c

void	*philosopher_right_action(void *arg);
void	*philosopher_left_action(void *arg);

// init.c

t_philosopher	*init_philosopher_arr(size_t length,
	size_t max_day,
	sem_t *hand_lock,
	pthread_mutex_t *mutex);
sem_t	*init_multisems(size_t length);

#endif
