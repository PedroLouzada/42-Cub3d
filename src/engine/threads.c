#include "thread.h"


void *swimming(void *arg)
{
    (void)arg;
    // while (1)
    // {

    // }
    return (NULL);
}

static  void    _deploy(t_thread *this, void(*f)(void *arg))
{

}

static  void    _set(t_thread *this, void *arg, void *value)
{
    const t_thread_plus *new = (t_thread_plus *)this;

    pthread_mutex_lock(&new->mutex);
    arg = value;
    pthread_mutex_unlock(&new->mutex);
}

static  void    *_get(t_thread *this, void *arg)
{

}
{
    const t_thread_plus *new = (t_thread_plus *)this;

    pthread_mutex_lock(&new->mutex);
    arg = value;
    pthread_mutex_unlock(&new->mutex);
}

t_thread *init_thread(int n)
{
    int i;
    static    t_thread_plus new;

    i = -1;
    new.deploy = _deploy;
    new.set = _set;
    new.get = _get;
    new.thread_id = ft_calloc(n , sizeof(pthread_t));
    if (!new.thread_id)
        exit_game("Memory Allocation\n");
    while (++i < n)
        new.thread_id[i] = pthread_create(&new.thread_id[i], NULL, swimming, NULL);
    return ((t_thread *)&new);
}