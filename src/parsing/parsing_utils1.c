/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skvackov <skvackov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:30:00 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/03 22:50:00 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_single_word(char **words, int i)
{
	char	*temp;

	if (ft_strchr(words[i], '"'))
	{
		temp = dollar_check(words[i]);
		words[i] = remove_quotes_from_word(temp);
	}
	else
		words[i] = remove_quotes_from_word(words[i]);
}

static char	*allocate_and_duplicate_processed(const char *input)
{
	char	*processed;
	char	*result;

	processed = add_spaces_around_redirections(input);
	if (!processed)
		return (NULL);
	result = ft_strdup(processed);
	free(processed);
	return (result);
}

static void	process_character_in_quote_string(char *copy, int *i)
{
	if (copy[*i] == ' ')
		copy[*i] = 29;
	if (copy[*i] == '"')
		ft_move_brackets(copy, i, '"');
	else if (copy[*i] == '\'')
		ft_move_brackets(copy, i, '\'');
	else if (copy[*i] == '{')
		ft_move_brackets(copy, i, '}');
}

char	*prepare_quoted_string_helper(char *result)
{
	char	*copy;
	int		i;

	copy = result;
	i = 0;
	while (copy[i] != 0)
	{
		process_character_in_quote_string(copy, &i);
		i++;
	}
	return (copy);
}

char	*prepare_quoted_string_main(const char *input)
{
	char	*result;

	result = allocate_and_duplicate_processed(input);
	if (!result)
		return (NULL);
	return (prepare_quoted_string_helper(result));
}
