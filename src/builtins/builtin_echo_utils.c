/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:07:35 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 19:07:44 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isascii_nonum(char c)
{
	if (c >= '1' && c <= '9')
		return (1);
	return (0);
}

static int	ft_count_dots(char *arg)
{
	int	i;
	int	dots;

	dots = 0;
	i = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '.')
			dots++;
	}
	return (dots);
}

void	ft_write_expander_char(char *word)
{
	char	start_char;
	char	end_char;

	start_char = word[1];
	end_char = word[ft_strlen(word) - 2];
	if (start_char < end_char)
	{
		while (start_char <= end_char)
		{
			write(1, &start_char, 1);
			if (start_char != end_char)
				write(1, " ", 1);
			start_char++;
		}
	}
	else
	{
		while (start_char >= end_char)
		{
			write(1, &start_char, 1);
			if (start_char != end_char)
				write(1, " ", 1);
			start_char--;
		}
	}
}

void	ft_write_expander_num(int start_int, int end_int)
{
	if (start_int < end_int)
	{
		while (start_int <= end_int)
		{
			ft_putnbr_fd(start_int, 1);
			if (start_int != end_int)
				write(1, " ", 1);
			start_int++;
		}
	}
	else
	{
		while (start_int >= end_int)
		{
			ft_putnbr_fd(start_int, 1);
			if (start_int != end_int)
				write(1, " ", 1);
			start_int--;
		}
	}
}

void	ft_echo_expander(char *word)
{
	int		dots;
	char	**split;
	char	*temp;

	dots = ft_count_dots(word);
	temp = ft_strtrim(word, "{}");
	split = ft_split(temp, '.');
	if ((ft_strlen(split[0]) > 1) || ft_strlen(split[1]) > 1)
	{
		if ((ft_isdigit_array(split) == 0) && dots == 2)
			ft_write_expander_num(ft_atoi(split[0]), ft_atoi(split[1]));
		else
			write(1, word, ft_strlen(word));
	}
	else if (ft_isascii_nonum(split[0][0]) == 0
		&& ft_isascii_nonum(split[1][0]) == 0 && dots == 2)
		ft_write_expander_char(word);
	else
		write(1, word, ft_strlen(word));
	free(temp);
	free_split(split);
}
