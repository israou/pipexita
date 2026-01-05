/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:58:39 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/26 00:58:54 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*divising(char *s, char **reste)
{
	char	*line;
	char	*tmp;
	int		newindex;

	if (!s)
		return (NULL);
	if (*reste && **reste == '\0')
	{
		free(*reste);
		*reste = NULL;
		return (NULL);
	}
	newindex = checknewline(s);
	if (newindex == -1)
	{
		line = ft_strdup(s);
		free(*reste);
		*reste = ft_strdup("\0");
		return (line);
	}
	tmp = s;
	line = extraction(s, 0, newindex);
	*reste = extraction(s, newindex + 1, ft_strlen(s + newindex));
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	ssize_t		readd;
	static char	*stash;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	while (BUFFER_SIZE > 0)
	{
		readd = read(fd, buf, BUFFER_SIZE);
		if (readd == 0)
			return (free(buf), divising(stash, &stash));
		else if (readd == -1)
		{
			free(stash);
			stash = NULL;
			return (free(buf), NULL);
		}
		buf[readd] = '\0';
		stash = join4gnl(stash, buf);
		if (checknewline(stash) >= 0)
			return (free(buf), divising(stash, &stash));
	}
}
