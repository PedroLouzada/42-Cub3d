/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:06:07 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 19:11:06 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "cub3d.h"
# include <pthread.h>

typedef struct s_thread			t_thread;
typedef struct s_thread_plus	t_thread_plus;

typedef struct s_job
{
	void						(*function)(void *arg);
	void						*arg;
}								t_job;

struct							s_thread
{
	void						(*deploy)(t_thread *this, void (*f)(void *),\
	void *arg);
	void						(*destroy)(t_thread *this);
	void						(*wait)(t_thread *this, int n);
};

struct							s_thread_plus
{
	void						(*deploy)(t_thread *this, void (*f)(void *),\
	void *arg);
	void						(*destroy)(t_thread *this);
	void						(*wait)(t_thread *this, int n);
	void						(*clean)(t_thread_plus *this);
	int							to_do;
	int							index;
	int							size;
	bool						quit;
	pthread_t					*thread_id;
	pthread_mutex_t				mutex;
	pthread_cond_t				working;
	t_job						*queue;
	int							pending;
	int							number;
	pthread_cond_t				done;
};

t_thread						*init_tpool(int n);

#endif