/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:42 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/07 10:11:44 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr(char *str, int c)
{
	int	i;

	i = ft_strlen(str) - 1;
	if ((char)c == '\0')
		return ((char *)&str[i + 1]);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

static int	ft_check(char c, const char *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_check(s1[start], set) != 0)
		start++;
	end = ft_strlen(s1);
	if (s1[end - 1] == '\n')
		end--;
	while (end > start && ft_check(s1[end - 1], set) != 0)
		end--;
	str = (char *)malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
