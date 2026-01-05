/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:21:32 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/15 21:22:33 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	generate_processes(char **av, t_data *arg)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];

	if (pipe(fd) == -1)
		errors("pipe failat");
	pid1 = fork();
	if (pid1 == -1)
		errors("ERREUR LORS DE LA CREATION DU PROCESSUS CHILD 1\n");
	if (pid1 == 0)
		process_child1(arg, fd, av);
	pid2 = fork();
	if (pid2 == -1)
		errors("");
	if (pid2 == 0)
		process_child2(arg, fd, av);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
