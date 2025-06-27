/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:29:56 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 22:30:02 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_double_redir(const char *input, char *result, int *i, int *j)
{
	char	redir_char;

	redir_char = input[*i];
	add_space_before(result, j);
	result[(*j)++] = redir_char;
	result[(*j)++] = redir_char;
	*i += 2;
	if (input[*i] && input[*i] != ' ')
		result[(*j)++] = ' ';
}

void	handle_single_redir(const char *input, char *result, int *i, int *j)
{
	add_space_before(result, j);
	result[(*j)++] = input[(*i)++];
	if (input[*i] && input[*i] != ' ')
		result[(*j)++] = ' ';
}

char	*add_spaces_around_redirections(const char *input)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(input);
	result = malloc(len * 3 + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		process_character_in_redirection(input, result, &i, &j);
	}
	result[j] = '\0';
	return (result);
}
