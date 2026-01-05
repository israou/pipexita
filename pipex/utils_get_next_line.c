/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:01:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/04 01:09:26 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	checknewline(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i);
	else
		return (-1);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*pa;

	i = 0;
	len = ft_strlen(s);
	pa = (char *)malloc(sizeof(char) * (len + 1));
	if (!pa)
		return (NULL);
	while (i < len)
	{
		pa[i] = s[i];
		i++;
	}
	pa[i] = '\0';
	return (pa);
}

char	*join4gnl(char const *stash, char const *buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (stash == NULL)
		return (ft_strdup((char *)buf));
	line = (char *)malloc (sizeof(char) * (ft_strlen(stash) + \
			ft_strlen(buf) + 1));
	if (!line)
		return (0);
	while (stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	while (buf[j])
	{
		line[i + j] = buf[j];
		j++;
	}
	line[i + j] = '\0';
	free((char *) stash);
	return (line);
}

char	*extraction(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	str = (char *) malloc (sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
