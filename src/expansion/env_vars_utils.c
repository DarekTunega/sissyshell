/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:32:34 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/03 23:44:23 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*status_replace(char *word)
{
	int		i;
	char	*temp;
	char	*status;
	char	*updated_str;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$' && word[i + 1] == '?')
		{
			status = ft_itoa(g_exit);
			updated_str = ft_substr(word, 0, i);
			temp = ft_strjoin(updated_str, status);
			free(updated_str);
			free(status);
			updated_str = ft_strjoin(temp, word + i + 2);
			free(temp);
			free(word);
			word = updated_str;
			i = -1;
		}
		i ++;
	}
	return (word);
}

static char	*hhoommee(void)
{
	char	*temp;
	char	*output;

	temp = getenv("HOME");
	output = ft_strdup(temp);
	free(temp);
	return (output);
}

char	*tilda_replace(char *word)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '~' && word[i + 1] == '/')
		{
			path = ft_strtrim(word, "~");
			temp = ft_strjoin(getenv("HOME"), path);
			free(path);
			free(word);
			word = temp;
		}
		else if (word[i] == '~' && word[i + 1] == '\0')
		{
			free(word);
			word = hhoommee();
		}
		else if (word[i] == '~' && word[i + 1] != '/' && word[i + 1] != '\0')
			break ;
		i++;
	}
	return (word);
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
