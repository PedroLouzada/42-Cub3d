#ifndef THREAD_H
#define THREAD_H

#include "cub3d.h"
#include <pthread.h>

typedef struct s_thread t_thread;
typedef struct s_thread_plus t_thread_plus;

struct s_thread
{
	void (*deploy)(t_thread *this, void (*f)(void *arg));
	void (*set)(t_thread *this, void *arg, void *value);
	void *(*get)(t_thread *this, void *arg);
	void (*destroy)(t_thread *this);
};

struct s_thread_plus
{
	void (*deploy)(t_thread_plus *this, void (*f)(void *arg));
	void (*set)(t_thread_plus *this, void *arg, void *value);
	void *(*get)(t_thread_plus *this, void *arg);
	void (*destroy)(t_thread_plus *this);
	int number;
	int launch;
	pthread_t *thread_id;
	pthread_mutex_t mutex;
	void (*function)(void *arg);
	void (*clean)(t_thread_plus *this);
	void *arg;
};

t_thread *init_tpool(int n);

#endif