/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:30:00 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 22:30:00 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_character_in_redirection(const char *input, char *result,
		int *i, int *j)
{
	if (input[*i] == '"' || input[*i] == '\'')
		handle_quotes(input, result, i, j);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		handle_double_redir(input, result, i, j);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		handle_double_redir(input, result, i, j);
	else if (input[*i] == '>' || input[*i] == '<')
		handle_single_redir(input, result, i, j);
	else
		result[(*j)++] = input[(*i)++];
}

void	handle_quotes(const char *input, char *result, int *i, int *j)
{
	char	quote;

	quote = input[*i];
	result[(*j)++] = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		result[(*j)++] = input[(*i)++];
	if (input[*i])
		result[(*j)++] = input[(*i)++];
}

void	add_space_before(char *result, int *j)
{
	if (*j > 0 && result[*j - 1] != ' ')
		result[(*j)++] = ' ';
}
