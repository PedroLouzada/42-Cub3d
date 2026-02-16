#include "cub3d.h"

void	set_time(long *time)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) < 0)
		return ;
	*time = curr_time.tv_sec * 1000L + curr_time.tv_usec / 1000L;
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}