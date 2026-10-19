#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "../utils/utils.h"
# include <pthread.h>
# include <semaphore.h>
#include <time.h>

/**
 * - length: number_of_philosophers
 * - time_to_die: 
 * 		If a philosopher has not started eating within
 * 		time_to_die milliseconds since the start of their last meal
 * 		or the start of the simulation, they die.
 * - time_to_eat (in milliseconds):
 * 		The time it takes for a philosopher to eat.
 * - time_to_sleep:
 * 		The time a philosopher will spend sleeping.
 * - time_to_live:
 * 		number_of_times_each_philosopher_must_eat.
 * 		0 = indefinitely until someone die from starvation.
 */
typedef struct t_philosopher
{
	size_t	name;
	size_t	length;
	bool	is_pick_left;
	bool	is_pick_right;
	bool	*is_loop;
	size_t	time_to_eat;
	size_t	time_to_die;
	size_t	current_time;
	size_t	time_to_live;
	size_t	time_to_sleep;
	size_t	prev_eat;
	pthread_mutex_t *fork_lock_l;
	pthread_mutex_t *fork_lock_r;
	pthread_mutex_t	*mutex;
}	t_philosopher;

typedef enum t_timetodo
{
	E_TIMETOLIVE,
	E_TIMETOEAT,
	E_TIMETODIE,
	E_TIMETOSLEEP,
}	t_timetodo;

typedef enum t_philo_action
{
	E_ACT_FORK,
	E_ACT_THINK,
	E_ACT_EAT,
	E_ACT_DIE,
	E_ACT_SLEEP,
}	t_philo_action;

// action.c

void	*philosopher_action(void *arg);
void	*philosopher_left_action(void *arg);
void	update_philosophers(t_philosopher *dst,
	size_t value, t_timetodo key, size_t length);

// init.c

t_philosopher	init_philosopher_unit(size_t i,
	size_t length,
	pthread_mutex_t *fork_lock,
	pthread_mutex_t *mutex);
t_philosopher	*init_philosopher_arr(size_t length,
	pthread_mutex_t *fork_lock,
	pthread_mutex_t *mutex);
pthread_mutex_t	*init_multisems(size_t length);

#endif
