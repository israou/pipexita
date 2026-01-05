/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:09:19 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/21 03:15:21 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**whereis_paths(t_data *arg)
{
	int		i;

	i = 0;
	while (arg->env[i])
	{
		if (ft_strncmp(arg->env[i], "PATH", 4) == 0)
		{
			arg->path = ft_split(arg->env[i] + 5, ':');
			if (arg->path)
				return (arg->path);
			else
				errors("ERROR: Cannot find PATH variable or split PATH failed");
		}
		i++;
	}
	errors("ERROR: PATH variable not found in environment");
	return (NULL);
}

char	*check_absolute_path(t_data *arg)
{
	if (arg->content[0][0] == '/' || arg->content[0][0] == '.')
	{
		if (access(arg->content[0], F_OK | X_OK) == -1)
			errors("error on thsi command");
		return (ft_strdup(arg->content[0]));
	}
	return (NULL);
}

char	*add_slash_to_path(t_data *arg)
{
	int		i;
	char	*tmp;
	char	*cmd_w_slash;
	char	*absolute_path;

	i = 0;
	cmd_w_slash = NULL;
	arg->path = whereis_paths(arg);
	absolute_path = check_absolute_path(arg);
	if (absolute_path)
		return (free_path(arg), absolute_path);
	while (arg->path[i])
	{
		tmp = ft_strjoin(arg->path[i], "/");
		if (tmp)
		{
			cmd_w_slash = ft_strjoin(tmp, arg->content[0]);
			free(tmp);
			if (cmd_w_slash && access(cmd_w_slash, F_OK | X_OK) == 0)
				return (free_path(arg), cmd_w_slash);
			free(cmd_w_slash);
		}
		i++;
	}
	return (NULL);
}

void	free_path(t_data *arg)
{
	int	j;

	j = 0;
	while (arg->path[j])
		free(arg->path[j++]);
	free(arg->path);
	arg->path = NULL;
}
