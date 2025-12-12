#include "cub3d.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_isdigit(int c);

void	clear_image(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->map[0]->textures[i])
			mlx_destroy_image(game->mlx->mlx, game->map[0]->textures[i]);
	}
}

void	parse_exit(char *s, char *arg, int fd)
{
	int		len;
	t_game	*game;

	game = get_game_addr(NULL);
	len = ft_strlen(s);
	write(2, "Error\n", 6);
	write(2, s, len);
	free(arg);
	clear_image(game);
	free_double(game->map[0]->map);
	free(game->map);
	mlx_destroy_display(game->mlx->mlx);
	free(game->mlx->mlx);
	if (fd > 0)
		close(fd);
	exit(1);
}

int	ft_isempty(char c)
{
	if (c == 32 || c == '\0' || (c >= 7 && c <= 13))
		return (1);
	return (0);
}

int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == '\n' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E' || c == 'D')
		return (1);
	return (0);
}
int	check_map_len(char *str)
{
	int	len;
	int	tail;

	len = ft_strlen(str);
	if (len < 5)
		return (0);
	tail = len - 5;
	if (str[tail] == '/' || ft_isempty(str[tail]))
		return (0);
	return (1);
}

void	check_sintax(char *str)
{
	char *tail;

	tail = ft_strrchr(str, '.');
	if (!tail || ft_strncmp(tail, ".cub", 5))
		parse_exit("Map must end with .cub\n", NULL, -1);
	if (!check_map_len(str))
		parse_exit("Map must have more than .cub\n", NULL, -1);
}