/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:08:58 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/21 03:13:58 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	all_redirections(int i, int *fd, char **av, t_data *arg)
{
	int	ac;

	ac = count_arguments(av);
	if (i != 2)
		redirect_input(fd);
	else
		redirect_input_for_firstcmd(arg, av);
	if (pipe(fd) == -1)
		errors("ERROR: CREATION PIPE FAILED\n");
	if (i != ac - 2)
		redirect_output(fd);
	else
		last_cmd(ac, av, arg);
}

void	to_free(char **to_free)
{
	int	j;

	j = 0;
	while (to_free[j])
		free(to_free[j++]);
	free(to_free);
}

void	redirect_multiples_cmd(t_data *arg, int ac, char **av)
{
	int	i;
	int	fd[2];
	int	in;
	int	out;

	i = 2;
	in = dup(0);
	out = dup(1);
	arg->prcss = count_commands(av, ac);
	while (i < ac - 1)
	{
		all_redirections(i, fd, av, arg);
		close(fd[1]);
		arg->content = ft_split_spaces(av[i]);
		arg->cmd = add_slash_to_path(arg);
		execute_cmds(arg, fd);
		to_free(arg->content);
		free(arg->cmd);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		i++;
	}
	end(arg);
}

void	execute_cmds(t_data *arg, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		errors("ERROR: FORK FAILED\n");
	else if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		if (execve(arg->cmd, arg->content, arg->env) == -1)
			perror("ERROR EXECUTING COMMAND\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*arg;

	if (ac < 5)
		errors("NOT ENOUGH ARGUMENTS\n");
	arg = (t_data *)malloc(sizeof(t_data));
	if (!arg)
	{
		errors("MEMORY ALLOCATION FAILED!\n");
	}
	if (ft_strncmp(av[1], "here_doc", 10) == 0)
	{
		arg->env = env;
		arg->limiter = av[2];
		arg->cmd1 = av[3];
		arg->cmd2 = av[4];
		here_doc(arg, ac, av);
	}
	else if (ft_strncmp(av[1], "here_doc", 10) != 0)
	{
		arg->env = env;
		redirect_multiples_cmd(arg, ac, av);
	}
}
