#include "cub3d.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_sleep(unsigned long time)
{
	unsigned long	deadline;

	deadline = get_time() + time;
	while (get_time() < deadline);
}