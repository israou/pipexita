/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:39:34 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/21 02:47:04 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_child1(t_data *arg, int *fd, char *av[])
{
	arg->content = ft_split_spaces(av[2]);
	close(fd[0]);
	arg->input_file = open(av[1], O_RDONLY, 0666);
	if (arg->input_file == -1)
	{
		close_and_print_error(fd, 1, "ERROR OPENING INPUT FILE\n");
		process_child2(arg, fd, av);
	}
	if (dup2(arg->input_file, STDIN_FILENO) == -1)
	{
		close_and_print_error(fd, arg->input_file, \
		"ERROR IN REDIRECTION TO STDIN\n");
		process_child2(arg, fd, av);
	}
	close(arg->input_file);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close_and_print_error(fd, 1, "ERROR IN REDIRECTION TO STDOUT");
		process_child2(arg, fd, av);
	}
	close(fd[1]);
	execute_command(arg);
	perror("ERREUR LORS DE L'EXECUTION DE LA 1ERE CMD");
	process_child2(arg, fd, av);
}

void	process_child2(t_data *arg, int *fd, char *av[])
{
	arg->content = ft_split_spaces(av[3]);
	close(fd[1]);
	arg->output_file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (arg->output_file == -1)
		errors("ERROR OPENING OUTPUT FILE");
	if (dup2(arg->output_file, STDOUT_FILENO) == -1)
	{
		perror("ERROR IN REDIRECTIOON TO STDOUT\n");
		close(arg->output_file);
		exit(EXIT_FAILURE);
	}
	close(arg->output_file);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		errors("ERROR IN REDIRECTION TO STDIN\n");
		close(fd[0]);
	}
	close(fd[0]);
	execute_command_two(arg);
	errors("ERREUR LORS DE L'EXECUTION DE LA CMD2");
}

void	execute_command(t_data *arg)
{
	arg->cmd = add_slash_to_path(arg);
	if (!arg->cmd)
		errors("ERROR: command not found");
	execve(arg->cmd, arg->content, arg->env);
	errors("ERROR: EXECUTING COMMAND 1\n");
}

void	execute_command_two(t_data *arg)
{
	arg->cmd2 = add_slash_to_path(arg);
	if (!arg->cmd2)
		errors("ERROR: command not found");
	execve(arg->cmd2, arg->content, arg->env);
	errors("ERROR EXECUTING COMMAND 2\n");
}

int	main(int ac, char **av, char **env)
{
	t_data	*arg;

	arg = (t_data *)malloc(sizeof(t_data));
	if (arg == NULL)
		errors("ERROR: arg allocation");
	arg->env = env;
	arg->cmd = av[2];
	arg->cmd2 = av[3];
	if (ac == 5)
	{
		generate_processes(av, arg);
	}
	else
	{
		errors("FAILURE");
		exit(EXIT_FAILURE);
	}
	return (0);
}
