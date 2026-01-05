/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:40:50 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/17 18:40:14 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**path;
	char	**env;
	char	**content;
	char	*cmd;
	char	*cmd2;
	int		input_file;
	int		output_file;
	char	*cmd_w_slash;
}			t_data;

int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, char *s2, unsigned int n);
char	**whereis_paths(t_data *data);
char	*add_slash_to_path(t_data *arg);
void	process_child1(t_data *arg, int *fd, char *av[]);
void	process_child2(t_data *arg, int *fd, char *av[]);
char	*ft_strchr(const char *s, int c);
void	execute_command(t_data *arg);
void	errors(char	*str);
void	execute_command_two(t_data *arg);
char	**ft_split_spaces(char *str);
void	generate_processes(char **av, t_data *arg);
void	close_and_print_error(int *fd, int to_close, char *error);

#endif