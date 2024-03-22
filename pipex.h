/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:40:50 by ichaabi           #+#    #+#             */
/*   Updated: 2024/03/22 00:57:56 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# include <unistd.h>//open, close, write, read
# include <stdlib.h>//malloc, free, exit
# include <stdio.h>//prerror
#	include <fcntl.h>


typedef struct s_data
{
	char	**path;
	char	**env;
	char	**content;
	char	*cmd;
	char	*cmd_p;
	int		input_file;
	int		output_file;
	int		*fd;

}			t_data;


int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, char *s2, unsigned int n);
char	**whereis_paths(t_data *data);
char	*add_slash_to_path(t_data *arg);
void	free_path(t_data *arg);
void	free_cmd(t_data *arg);
void	processus_fils(int *fd, char *av[], char *env[]);
void	processus_parent(int *fd, char *av, char *env);

// char	*check_env(t_data *data);



#endif