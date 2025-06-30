/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:32:03 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/02 22:33:00 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_replacement(char *word, int i, int j)
{
	char	*env_v;
	char	*temp;
	char	*updated_str;

	updated_str = NULL;
	temp = ft_substr(word, i + 1, j);
	env_v = getenv(temp);
	if (env_v == NULL)
		env_v = "";
	free(temp);
	updated_str = ft_substr(word, 0, i);
	temp = ft_strjoin(updated_str, env_v);
	free(updated_str);
	updated_str = ft_strjoin(temp, word + i + j + 1);
	free(temp);
	free(word);
	return (updated_str);
}

static char	*process_dollar_expansion(char *word, int *i, int *j)
{
	while (ft_isalnum(word[*i + 1 + *j]) || word[*i + 1 + *j] == '_')
		(*j)++;
	if (*j != 0)
	{
		word = env_replacement(word, *i, *j);
		*i = -1;
		*j = 0;
		return (word);
	}
	return (word);
}

char	*dollar_check(char *word)
{
	int		i;
	int		j;
	bool	in_single_quotes;

	i = 0;
	j = 0;
	in_single_quotes = false;
	while (word[i] != '\0')
	{
		if (word[i] == '\'' && (i == 0 || word[i - 1] != '\\'))
			in_single_quotes = !in_single_quotes;
		else if (word[i] == '$' && !in_single_quotes && (i == 0 || word[i - 1] != '\\'))
		{
			word = process_dollar_expansion(word, &i, &j);
			if (i == -1)
				in_single_quotes = false;
		}
		i++;
	}
	return (word);
}

static bool	should_expand_variables(char *word)
{
	int		i;
	bool	in_single_quotes;
	bool	has_expandable_content;

	i = 0;
	in_single_quotes = false;
	has_expandable_content = false;
	while (word[i] != '\0')
	{
		if (word[i] == '\'' && (i == 0 || word[i - 1] != '\\'))
		{
			in_single_quotes = !in_single_quotes;
		}
		else if (word[i] == '$' && !in_single_quotes && (i == 0 || word[i - 1] != '\\'))
		{
			has_expandable_content = true;
		}
		i++;
	}
	return (has_expandable_content);
}

char	**replace_env_var_nonquated(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (should_expand_variables(words[i]))
			words[i] = dollar_check(words[i]);
		i++;
	}
	return (words);
}

char	**status_var_check(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (ft_strchr(words[i], '$'))
			words[i] = status_replace(words[i]);
		else if (ft_strchr(words[i], '~'))
			words[i] = tilda_replace(words[i]);
		i ++;
	}
	return (words);
}
