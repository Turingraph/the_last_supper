/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phsottat <phsottat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:27:58 by phsottat          #+#    #+#             */
/*   Updated: 2026/10/22 12:29:12 by phsottat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

/**
 * - length: number_of_philos
 * - time_to_die: 
 * 		If a philo has not started eating within
 * 		time_to_die milliseconds since the start of their last meal
 * 		or the start of the simulation, they die.
 * - time_to_eat (in milliseconds):
 * 		The time it takes for a philo to eat.
 * - time_to_sleep:
 * 		The time a philo will spend sleeping.
 * - time_to_live:
 * 		number_of_times_each_philo_must_eat.
 * 		0 = indefinitely until someone die from starvation.
 */
typedef struct t_philo
{
	size_t			name;
	size_t			length;
	bool			is_pick_left;
	bool			is_pick_right;
	bool			*is_loop;
	size_t			*current_time;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			current_iter;
	size_t			time_to_live;
	size_t			time_to_sleep;
	size_t			prev_eat;
	pthread_mutex_t	*fork_lock_l;
	pthread_mutex_t	*fork_lock_r;
	pthread_mutex_t	*mutex;
}	t_philo;

typedef enum t_timetodo
{
	E_TIMETOLIVE,
	E_TIMETOEAT,
	E_TIMETODIE,
	E_TIMETOSLEEP,
}	t_timetodo;

typedef enum t_philo_action
{
	E_ACT_FORK_L,
	E_ACT_FORK_R,
	E_ACT_THINK,
	E_ACT_EAT,
	E_ACT_DIE,
	E_ACT_SLEEP,
}	t_philo_action;

// action.c

void			*philo_action(void *arg);
void			*philo_left_action(void *arg);
void			update_philos(t_philo *dst,
					size_t value, t_timetodo key, size_t length);

// atoi.c

int				f_atoi(const char *src,
					bool *is_int, const char *base, size_t digits);
size_t			ft_putnbr_fd(int n, int fd, const char *base, size_t digits);

// init.c

t_philo			init_philo_unit(size_t i,
					size_t length,
					pthread_mutex_t *fork_lock,
					pthread_mutex_t *mutex);
t_philo			*init_philo_arr(size_t length,
					pthread_mutex_t *fork_lock,
					pthread_mutex_t *mutex);
pthread_mutex_t	*init_multisems(size_t length);

// math.c

int				f_abs(int x);

// string.c

void			*malloc_talk(size_t elem_size, const char *comment);
size_t			f_strlen(const char *str);
size_t			knight_of_coin(const char *str, char stop);

// utils.c

bool			f_is_loop(const t_philo *src);
void			write_philo_record(
					const t_philo *philo, t_philo_action action);
size_t	get_current_time(void);

#endif
