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

int	handle_variable_expansion(char *word, char *result, int i, int j)
{
	int		k = 0;
	char	*var;
	char	*env_v;

	while (ft_isalnum(word[i + 1 + k]) || word[i + 1 + k] == '_')
		k++;
	if (k == 0)
		return (0);
	var = ft_substr(word, i + 1, k);
	env_v = getenv(var);
	free(var);
	if (env_v)
		while (*env_v)
			result[j++] = *env_v++;
	return (k + 1);
}

char	*dollar_check(char *word)
{
	int		len = ft_strlen(word);
	char	*result = malloc(len + 1);
	int		i = 0, j = 0, skip;

	while (word[i])
	{
		if (word[i] == '\\' && word[i + 1] == '$')
		{
			result[j++] = '\\';
			result[j++] = '$';
			i += 2;
		}
		else if (word[i] == '$' && (skip = handle_variable_expansion(word, result, i, j)))
			i += skip;
		else
			result[j++] = word[i++];
	}
	result[j] = '\0';
	free(word);
	return (result);
}

char	**replace_env_var_nonquated(char **words)
{
	int	i;
	int	len;

	i = 0;
	while (words[i] != NULL)
	{
		len = ft_strlen(words[i]);
		if (!(words[i][0] == '\'' && words[i][len - 1] == '\''))
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
