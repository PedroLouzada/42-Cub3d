/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:59 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 18:30:41 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_strlen(char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len])
	{
		if (s[len++] == '\n')
			break ;
	}
	return (len);
}

static char	*buffer_clear(char *s, int f)
{
	int	i;
	int	j;

	j = 0;
	if (!f)
	{
		i = get_strlen(s);
		while (s[i + j])
		{
			s[j] = s[i + j];
			j++;
		}
	}
	while (s[j])
		s[j++] = '\0';
	return (s);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	str = malloc((get_strlen(s1) + get_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i++] = s2[j];
		if (s2[j++] == '\n')
			break ;
	}
	str[i] = '\0';
	return (free(s1), str);
}

static int	check_newline(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	s[11];
	char		*line;
	int			rd;

	if (fd < 0)
		return (NULL);
	rd = 1;
	line = NULL;
	while (1)
	{
		if (*s == '\0')
			rd = read(fd, s, 10);
		if (rd < 0)
			return (buffer_clear(s, 1), free(line), NULL);
		if (rd == 0)
			return (line);
		line = ft_strjoin(line, s);
		if (!line)
			return (buffer_clear(s, 1), NULL);
		buffer_clear(s, 0);
		if (line && check_newline(line))
			break ;
	}
	return (line);
}
