/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:05:27 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/16 19:24:33 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	countword(const char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*get_word(const char *s, char c, int *i)
{
	char	*ptr;
	int		start;
	int		len;
	int		k;

	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	len = *i - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	k = 0;
	while (*i - start > k)
	{
		ptr[k] = s[start + k];
		k++;
	}
	ptr[k] = '\0';
	return (ptr);
}

static char	**ft_free(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		wc;
	int		r;
	int		i;

	if (!s)
		return (NULL);
	wc = countword(s, c);
	res = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!res)
		return (free((char *)s), NULL);
	r = 0;
	i = 0;
	while (wc > r)
	{
		res[r] = get_word(s, c, &i);
		if (!res[r])
			return (free((char *)s), ft_free(res));
		r++;
	}
	res[wc] = NULL;
	return (res);
}
