/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:31 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 19:01:59 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_isdigit(int c);

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
	const int	len = ft_strlen(str);
	int			tail;

	if (len < 5)
		return (0);
	tail = len - 5;
	if (str[tail] == '/' || ft_isempty(str[tail]))
		return (0);
	return (1);
}

void	check_sintax(char *str)
{
	char	*tail;

	tail = ft_strrchr(str, '.');
	if (!tail || ft_strncmp(tail, ".cub", 5))
		parse_exit("Map must end with .cub\n", NULL, -1, 0);
	if (!check_map_len(str))
		parse_exit("Map must have more than .cub\n", NULL, -1, 0);
}
