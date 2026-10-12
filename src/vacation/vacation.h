#ifndef VACATION_H
# define VACATION_H

# include "../utils/utils.h"
# include <pthread.h>
# include <semaphore.h>

typedef struct t_home
{
	int		visitor;
	int		prev_visitor;
}	t_home;

typedef struct t_visitor
{
	size_t		length;
	size_t		record_time;
	size_t		max_record_time;
	size_t		name;
	size_t		current_address;
	size_t		car_speed;
	pthread_mutex_t *mutex;
	sem_t *clients;
	sem_t *server;
}	t_visitor;

typedef struct t_traveloka
{
	size_t		length;
	sem_t *clients;
	size_t	max_record_time;
	sem_t *server;
}	t_traveloka;

// init.c

t_visitor	*init_visitors(size_t *arg_length, int len);
void	init_visitor_mutex(t_visitor *arg, pthread_mutex_t *mutex, sem_t *clients, sem_t *server);

// loop.c

void	*vacation_action(void *arg);

// server.c

void	*traveloka_action(void *arg);

#endif

/*
::: 002 live at 002 (0-th day, 002 != 002)
::: 002 live at 000 (1-th day, 002 != -01)
::: 000 live at 002 (0-th day, 000 != 002)
::: 000 live at 003 (1-th day, 000 != -01)
::: 004 live at 002 (0-th day, 004 != 000)
::: 004 live at 001 (1-th day, 004 != -01)
::: 003 live at 002 (0-th day, 003 != 004)
::: 003 live at 004 (1-th day, 003 != 004)
::: 001 live at 002 (0-th day, 001 != 003)
::: 001 live at 002 (1-th day, 001 != 001)
*/