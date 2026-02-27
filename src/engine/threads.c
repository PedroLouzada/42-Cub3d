#include "thread.h"

void *swimming(t_thread_plus *this)
{
    void *arg;

    while (1)
    {
        arg = this->get(this, this->launch);
        if ((int)arg > 0)
            todo;
        usleep(100);
    }
    return (NULL);
}

static void _deploy(t_thread *this, void (*f)(void *arg))
{
    t_thread_plus *new;

    new = (t_thread_plus *)this;
    new->set(this, new->launch, new->launch + 1);


}

static void _set(t_thread *this, void *arg, void *value)
{
    const t_thread_plus *new = (t_thread_plus *)this;

    pthread_mutex_lock(&new->mutex);
    arg = value;
    pthread_mutex_unlock(&new->mutex);
}

static void *_get(t_thread *this, void *arg)
{
    void *temp;
    const t_thread_plus *new = (t_thread_plus *)this;

    pthread_mutex_lock(&new->mutex);
    temp = arg;
    pthread_mutex_unlock(&new->mutex);
    return (temp);
}
void    _destroy(t_thread *this)
{
    const t_thread_plus *new = (t_thread_plus *)this;

    free(new->thread_id);
    pthread_mutex_destroy(&new->mutex);
}

t_thread *init_tpool(int n)
{
    int i;
    static t_thread_plus new;

    i = -1;
    new.number = n;
    new.deploy = _deploy;
    new.set = _set;
    new.get = _get;
    new.destroy = _destroy;
    pthread_mutex_init(&new.mutex, NULL);
    new.thread_id = ft_calloc(n, sizeof(pthread_t));
    if (!new.thread_id)
        exit_game("Memory Allocation\n");
    while (++i < n)
    {
        new.thread_id[i] = pthread_create(&new.thread_id[i], NULL, swimming, &new);
        pthread_detach(new.thread_id[i]);
    }
    return ((t_thread *)&new);
}
