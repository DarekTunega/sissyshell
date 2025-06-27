/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:29:32 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 22:29:39 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prepare_quoted_string(const char *input)
{
	return (prepare_quoted_string_main(input));
}

char	**parse_quated_strings(char **words)
{
	int		i;

	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '"') || ft_strchr(words[i], '\''))
			process_single_word(words, i);
		i++;
	}
	return (words);
}
