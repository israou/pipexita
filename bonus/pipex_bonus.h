/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:03:21 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/21 02:59:32 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_data
{
	char	**path;
	char	**env;
	char	**content;
	int		input_file;
	int		output_file;
	char	*cmd_w_slash;
	char	**cmds;
	char	*cmd;
	int		prcss;
	int		here_doc;
	char	*limiter;
	char	*cmd1;
	char	*cmd2;
}			t_data;

void	here_doc(t_data *arg, int ac, char **av);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, char *s2, unsigned int n);
void	errors(char	*str);
char	**ft_split_spaces(char *str);
char	**whereis_paths(t_data *arg);
char	*add_slash_to_path(t_data *arg);
int		count_commands(char **args, int ac);
void	redirect_input_for_firstcmd(t_data *arg, char **av);
void	redirect_output(int *fd);
void	redirect_multiples_cmd(t_data *arg, int ac, char **av);
void	execute_cmds(t_data *arg, int *fd);
void	last_cmd(int ac, char **av, t_data *arg);
void	redirect_input(int *fd);
int		count_arguments(char **av);
void	end(t_data *arg);
void	read_the_input(t_data *arg, int *fd);
void	execute_cmd_two(t_data *arg, int ac, char **av);
char	*get_next_line(int fd);
char	*divising(char *s, char **reste);
int		checknewline(char *s);
char	*ft_strdup(char *s);
char	*join4gnl(char const *stash, char const *buf);
char	*extraction(char const *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);
void	fork_for_execute(t_data *arg, int ac, char **av);
void	to_free(char **to_free);
void	free_path(t_data *arg);
void	all_redirections(int i, int *fd, char **av, t_data *arg);
char	*check_absolute_path(t_data *arg);

#endif