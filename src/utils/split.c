/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:57:17 by pbongiov          #+#    #+#             */
/*   Updated: 2026/03/15 21:11:11 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_words(char *s, char c)
{
	int	count;
	int	new_word;

	count = 0;
	new_word = 0;
	while (*s)
	{
		if (*s != c && new_word == 0)
		{
			new_word = 1;
			count++;
		}
		else if (*s == c)
			new_word = 0;
		s++;
	}
	return (count);
}

static char	*sep_word(char *s, char c)
{
	int		len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	**ft_lesslines(char **str, char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			str[i] = sep_word(s, c);
			if (!str[i])
			{
				ft_free(str);
				return (NULL);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (ft_lesslines(str, s, c));
}