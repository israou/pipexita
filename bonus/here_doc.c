/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:03:52 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/17 21:53:07 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	read_the_input(t_data *arg, int *fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (line[0] == '\0' || line == NULL)
		{
			free(line);
			continue ;
		}
		if (ft_strcmp(line, arg->limiter) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

void	here_doc(t_data *arg, int ac, char **av)
{
	int		pid;
	int		fd[2];

	if (ac < 6)
		errors("INVALID NUMBER OF ARGUMENTS\n");
	if (pipe(fd) == -1)
		errors("pipe failed");
	pid = fork();
	if (pid == -1)
		errors("fork failed");
	if (pid == 0)
	{
		close(fd[0]);
		read_the_input(arg, fd);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	wait(NULL);
	fork_for_execute(arg, ac, av);
}

void	fork_for_execute(t_data *arg, int ac, char **av)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		errors("pipe failed");
	pid = fork();
	if (pid == -1)
		errors("fork failed");
	if (pid == 0)
	{
		arg->content = ft_split_spaces(av[3]);
		arg->cmd1 = add_slash_to_path(arg);
		close(fd[0]);
		dup2(fd[1], 1);
		execve(arg->cmd1, arg->content, arg->env);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	wait(NULL);
	arg->content = ft_split_spaces(av[4]);
	execute_cmd_two(arg, ac, av);
}

void	execute_cmd_two(t_data *arg, int ac, char **av)
{
	arg->cmd2 = add_slash_to_path(arg);
	arg->output_file = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (arg->output_file == -1)
		errors("error opening output file for here_doc\n");
	dup2(arg->output_file, 1);
	if (execve(arg->cmd2, arg->content, arg->env) == -1)
		errors("error executing command\n");
}
