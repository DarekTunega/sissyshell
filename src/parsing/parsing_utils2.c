/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skvackov <skvackov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:29:00 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/03 22:50:00 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_move_brackets(char *copy, int *i, char bracket)
{
	(*i)++;
	while (copy[*i] != 0 && copy[*i] != bracket)
		(*i)++;
}

char	*remove_quotes_from_word(char *word)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(word) + 1);
	if (!result)
		return (word);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
			copy_quoted_content(word, result, &i, &j);
		else
			result[j++] = word[i++];
	}
	result[j] = '\0';
	free(word);
	return (result);
}

void	handle_escape_in_quotes(char *word, char *result, int *i, int *j)
{
	if (word[*i + 1] == '$')
	{
		result[(*j)++] = '$';
		(*i) += 2;
	}
	else if (word[*i + 1] == '\\')
	{
		result[(*j)++] = '\\';
		(*i) += 2;
	}
	else
		result[(*j)++] = word[(*i)++];
}

void	copy_quoted_content(char *word, char *result, int *i, int *j)
{
	char	quote_char = word[*i];

	(*i)++;
	while (word[*i] && word[*i] != quote_char)
	{
		if (quote_char == '"' && word[*i] == '\\')
			handle_escape_in_quotes(word, result, i, j);
		else
			result[(*j)++] = word[(*i)++];
	}
	if (word[*i] == quote_char)
		(*i)++;
}
