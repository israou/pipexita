/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:48:26 by ichaabi           #+#    #+#             */
/*   Updated: 2024/04/16 19:24:00 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s2[i] && i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

static	int	count_word(char *str)
{
	int	wrd;
	int	i;

	wrd = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wrd++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
	}
	return (wrd);
}

char	**ft_split_spaces(char *str)
{
	char	**otp;
	int		wrd;
	int		ptr;
	int		i;
	int		j;

	ptr = 0;
	wrd = count_word(str);
	otp = malloc((wrd + 1) * sizeof(char *));
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		j = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		if (i > j)
		{
			otp[ptr] = malloc(i - j + 1);
			ft_strncpy(otp[ptr++], &str[j], i - j);
		}
	}
	otp[ptr] = NULL;
	return (otp);
}
