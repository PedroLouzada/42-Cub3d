#include "thread.h"

void	swimming(void *p)
{
	t_job			job;
	t_thread_plus	*this;

	this = p;
	while (1)
	{
		pthread_mutex_lock(&this->mutex);
		while (!this->to_do && !this->quit)
			pthread_cond_wait(&this->working, &this->mutex);
		if (this->quit)
		{
			pthread_mutex_unlock(&this->mutex);
			break ;
		}
		job = this->queue[this->index];
		this->index = (this->index + 1) % 10;
		this->to_do--;
		pthread_mutex_unlock(&this->mutex);
		if (job.function)
			job.function(job.arg);
	}
	return ;
}

static void	_deploy(t_thread *this, void (*f)(void *), void *arg)
{
	t_thread_plus	*new;

	new = (t_thread_plus *)this;
	pthread_mutex_lock(&new->mutex);
	if (new->size == 10)
	{
		pthread_mutex_unlock(&new->mutex);
		return ;
	}
	new->queue[new->size].function = f;
	new->queue[new->size].arg = f;
	new->size = (new->size + 1) % 10;
	new->to_do++;
	pthread_cond_signal(&new->working);
	pthread_mutex_unlock(&new->mutex);
}

void	_destroy(t_thread *this)
{
	t_thread_plus	*new;

	new = (t_thread_plus *)this;
	free(new->thread_id);
	pthread_mutex_destroy(&new->mutex);
}

t_thread	*init_tpool(int n)
{
	int						i;
	static t_thread_plus	new;

	i = -1;
	new.deploy = _deploy;
	new.destroy = _destroy;
	pthread_cond_init(&new.working, NULL);
	pthread_mutex_init(&new.mutex, NULL);
	new.queue = ft_calloc(10, sizeof(t_job));
	new.thread_id = ft_calloc(n, sizeof(pthread_t));
	if (!new.thread_id || !new.queue)
		exit_game("Memory Allocation\n");
	while (++i < n)
	{
		pthread_create(&new.thread_id[i], NULL, (void *)swimming, &new);
		pthread_detach(new.thread_id[i]);
	}
	return ((t_thread *)&new);
}
