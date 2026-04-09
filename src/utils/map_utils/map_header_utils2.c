/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:10:00 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 18:42:29 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strtrim(char *s1, char *set);

void	skip_spaces(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

void	open_path(char *root, char *str, int fd, int n)
{
	int	spr_fd;

	str = ft_strtrim(str + 2, " ");
	if (!str)
		parse_exit("Memory Allocation\n\n", root, fd, 0);
	spr_fd = open(str, O_RDONLY);
	if (spr_fd < 0)
		parse_exit("Texture path not valid\n", root, fd, 0);
	close(spr_fd);
	if (game()->map[0]->textures[n])
		parse_exit("Double definition on wall texture\n", root, fd, 0);
	game()->map[0]->textures[n] = new_img(str);
	if (!game()->map[0]->textures[n] || !game()->map[0]->textures[n]->img)
		parse_exit("Xpm file not valid\n", root, fd, 0);
	free(str);
}

void	check_textures(char *root, char *str, int fd)
{
	if (!ft_strncmp(str, "NO ", 3))
		open_path(root, str, fd, 0);
	else if (!ft_strncmp(str, "EA ", 3))
		open_path(root, str, fd, 1);
	else if (!ft_strncmp(str, "WE ", 3))
		open_path(root, str, fd, 2);
	else if (!ft_strncmp(str, "SO ", 3))
		open_path(root, str, fd, 3);
}

int	ft_isdigit_modified(int c)
{
	if ((c >= '0' && c <= '9') || c == ',')
		return (1);
	return (0);
}

int	parse_rgb(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[++i])
	{
		if (!ft_isdigit_modified(s[i]) && !ft_isempty(s[i]))
			return (0);
		if (s[i] == ',')
			j++;
	}
	if (j != 2)
		return (0);
	return (1);
}
