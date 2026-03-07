#include "cub3d.h"

void	*ft_calloc(size_t nm, size_t sz)
{
	size_t	size;
	t_str	data;
	void	*alloc;

	size = nm * sz;
	if (nm > SIZE_MAX / sz)
		return (NULL);
	if (!nm || !sz)
		size = 1;
	alloc = malloc(size);
	if (!alloc)
		return (NULL);
	data = (t_str)alloc;
	while (size--)
		*data++ = '\0';
	return (alloc);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*start;

	start = dest;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (start);
}

t_str	ft_joinstr(t_str s1, t_str s2)
{
	int		tln;
	t_str	str;

	if (!s1 || !s2)
		return (NULL);
	tln = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(tln, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy((str + ft_strlen(s1)), s2, ft_strlen(s2));
	return (str);
}

int	exit_game(char *str)
{
	int				i;
	int				j;
	t_thread_plus	*t;

	if (str)
		write(2, str, ft_strlen(str));
	game()->eng->pool->destroy(game()->eng->pool);
	clear_image();
	mlx_destroy_window(game()->mlx->mlx, game()->mlx->win);
	i = -1;
	while (++i < 6)
	{
		free_double(game()->map[i]->map);
		if (game()->map[i]->objs)
		{
			j = 0;
			while (game()->map[i]->objs[j])
				free(game()->map[i]->objs[j++]);
			free(game()->map[i]->objs);
		}
		free(game()->map[i]->rays[E]);
		free(game()->map[i]->rays[P]);
		if (i < 6)
			free(game()->map[i]);
	}
	mlx_destroy_display(game()->mlx->mlx);
	free(game()->mlx->mlx);
	free(game()->mlx);
	exit(0);
	return (0);
}
