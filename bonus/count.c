/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:59:00 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/16 20:26:22 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	count_commands(char **args, int ac)
{
	int	i;
	int	prcss;

	i = 2;
	prcss = 0;
	while (i < ac - 1)
	{
		if (args[i])
			prcss++;
		i++;
	}
	return (prcss);
}

int	count_arguments(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}
