/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:39:34 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/27 04:03:31 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**whereis_paths(t_data *arg)
{
	int		i;//parcourt la variable env,, puis les chemins extraits de paths

	i = 0;

	while (arg->env[i])
	{
		if (ft_strncmp(arg->env[i], "PATH", 4) == 0)
		{
			arg->path = ft_split(arg->env[i] + 5, ':');//deplacer le pointeur de 5 positions pour eliminer PATHS=
			if (arg->path)
				return (arg->path);
			else
				perror("ERROR\n path, split");
				exit(EXIT_FAILURE);
		}
		i++;
	}
	return (NULL);
}

//PATH contient une liste de répertoires où le système recherche les exécutables
//access()vérifie si le programme peut accéder au fichier pathname

char	*add_slash_to_path(t_data *arg)
{
	int		i;
	char	*tmp;
	char	*cmd_w_slash;

	i = 0;
	cmd_w_slash = NULL;
	arg->path = whereis_paths(arg);
	while (arg->path[i])
	{
		tmp = ft_strjoin(arg->path[i], "/");
		if (tmp)
		{
			cmd_w_slash = ft_strjoin(tmp, arg->content[0]);
			// printf(2, "%s\n", cmd_w_slash);
			free(tmp);
			if (cmd_w_slash && access(cmd_w_slash, F_OK | X_OK) == 0)//hyedt x_ok nshouf ghir wsh kayn
				return (cmd_w_slash);
			free(cmd_w_slash);
		}
		i++;
	}
	return (NULL);
}

//Par exemple, si arg->path[i] est "/usr/bin" et arg->cmd_p est "ls"
// la fonction crée un nouveau chemin "/usr/bin/ls",
// représentant le chemin complet de la commande "ls" située dans le répertoire "/usr/bin"


void close_and_print_error(int *fd, int to_close, char *error)
{
	perror(error);
	close(fd[to_close]);
}

void	process_child1(t_data *arg, int *fd, char *av[])
{
	arg->content = ft_split_spaces(av[2]);
	close(fd[0]);//processchild1 ne lira pas a partir du | car il doit se concentrer sur la lecture a partir de fichier d entrée specifiéas
	arg->input_file = open(av[1], O_RDONLY, 0666);//ouvrir le fichier d entrée en lecture seule
	if (arg->input_file == -1)
	{
		close_and_print_error(fd, 1, "ERROR OPENING INPUT FILE\n");
		process_child2(arg, fd, av);//cat | ls//exit
	}
	if (dup2(arg->input_file, STDIN_FILENO) == -1)
	{
		close_and_print_error(fd, arg->input_file, "ERROR IN REDIRECTION VERS STDIN\n");
		process_child2(arg, fd, av);//n exit
	}
	close(arg->input_file);//fermer le fichier d entrée apres redirection
	if (dup2(fd[1], STDOUT_FILENO) == -1)//hit l output likikhrej khass ndewzo lpipe bash tqrah lcommande lakhra
	{
		close_and_print_error(fd, 1, "ERROR IN REDIRECTION VERS STDOUT");
		process_child2(arg, fd, av);//n exit
	}
	close(fd[1]);
	execute_command(arg);
	perror("ERREUR LORS DE L'EXECUTION DE LA 1ERE CMD");
	process_child2(arg, fd, av);
}

void	process_child2(t_data *arg, int *fd, char *av[])
{
	arg->content = ft_split_spaces(av[3]);
	close(fd[1]);//fermer le fd stoutput,, il n ecrira pas dans |
	arg->output_file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);//O_TRUNC vide le fichier avant son ouverture
	if (arg->output_file == -1)
		errors("ERROR OPENING OUTPUT FILE");
	if (dup2(arg->output_file, STDOUT_FILENO) == -1)
	{
		perror("ERROR IN REDIRECTIOON VERS STDOUT\n");
		close(arg->output_file);
		exit(EXIT_FAILURE);
	}
	close(arg->output_file);//fermer en cas de succês
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		errors("ERROR IN REDIRECTION VERS STDIN\n");
		close(fd[0]);
	}
	close(fd[0]);
	// dprintf(2, "fdfddfd\n");
	execute_command_two(arg);
	errors("ERREUR LORS DE L'EXECUTION DE LA CMD2");
}
void	execute_command(t_data *arg)
{
	if (ft_strchr(arg->cmd, '/'))
	{
		if (access(arg->cmd, F_OK) == 0)
			return ;
		errors("cmd not found\n");
	}
	arg->cmd = add_slash_to_path(arg);
	if (!arg->cmd)
		errors("eerroorr\n");
	// dprintf(2, "%s````````````%s\n", arg->cmd_p, arg->cmd);
	execve(arg->cmd, arg->content, arg->env);
	errors("ERROR EXECUTING COMMAND 1\n");
}

void	execute_command_two(t_data *arg)
{
	if (ft_strchr(arg->cmd, '/'))
	{
		if (access(arg->cmd, F_OK) == 0)
			return ;
		errors("cmd not found\n");
	}
	arg->cmd2  = add_slash_to_path(arg);
	if (!arg->cmd2)
		errors("eerroorr\n");
	// dprintf(2, "%s````````````%s\n", arg->cmd_p, arg->cmd);
	execve(arg->cmd2, arg->content, arg->env);
	errors("ERROR EXECUTING COMMAND 2\n");
}
void generate_processes(int ac, char **av, t_data *arg)
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

int main(int ac, char **av, char **env)
{
	t_data	*arg;

	arg = (t_data *)malloc(sizeof(t_data));
	if (arg == NULL)
		errors("ARG ALLOCATION\n");
	arg->env = env;
	arg->cmd = av[2];
	arg->cmd2 = av[3];
	if (ac == 5)
	{
		generate_processes(ac, av, arg);
	}
	else
	{
		perror("FAILURE\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

//exemples
// step 1:
// 	PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
// step 2:
// 	path[0] = "/usr/local/bin/"
// 	path[1] = "/usr/bin/"
// 	path[2] = "/bin/"
// 	path[3] = "/usr/sbin/"
// 	path[4] = "/sbin/"
// 	path[5] = NULL
// int main(int ac, char **av, char **envp)
// {
// 	char *options[3] = {"ls", "-la", NULL};

// 	(void)ac;
// 	(void)av;
// 	execve("/bin/ls", options, envp);
// 	return (0);
// }