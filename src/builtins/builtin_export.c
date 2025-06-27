/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:06:51 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/02 19:08:10 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rewrite(int index, char *var, t_data *data)
{
	if (index >= 0 && data->minishell_env && data->minishell_env[index])
	{
		free(data->minishell_env[index]);
		data->minishell_env[index] = ft_strdup(var);
		environ[index] = data->minishell_env[index];
	}
	else if (index >= 0)
	{
		data->minishell_env[index] = ft_strdup(var);
		environ[index] = data->minishell_env[index];
	}
}

void	ft_add(char *var, t_data *data)
{
	char	**new_environ;
	char	*new_var;
	int		size;
	int		i;

	size = 0;
	i = -1;
	new_var = ft_strdup(var);
	while (environ[size] != NULL)
		size++;
	new_environ = malloc((size + 2) * sizeof(char *));
	while (++i < size)
		new_environ[i] = ft_strdup(environ[i]);
	new_environ[size] = new_var;
	new_environ[size + 1] = NULL;
	free_split(data->minishell_env);
	data->minishell_env = new_environ;
	environ = new_environ;
}

void	ft_export_fork(char **words, t_data *data)
{
	char	**split;
	int		i;
	int		existing_index;
	char	*arg;

	i = 1;
	while (words[i] != NULL)
	{
		if ((ft_checkarg(words[i])) != NULL)
		{
			split = ft_split(words[i], '=');
			existing_index = ft_checkforexisting(split[0]);
			arg = ft_checkarg(words[i]);
			if (existing_index != -1)
				ft_rewrite(existing_index, arg, data);
			else
				ft_add(arg, data);
			free_split(split);
		}
		i++;
	}
	fork_exit(0, data);
}

int	ft_export_nonfork(char **words, t_data *data)
{
	char	**split;
	int		i;
	int		existing_index;
	char	*arg;

	i = 1;
	while (words[i] != NULL)
	{
		if ((ft_checkarg(words[i])) != NULL)
		{
			split = ft_split(words[i], '=');
			existing_index = ft_checkforexisting(split[0]);
			arg = ft_checkarg(words[i]);
			if (existing_index != -1)
				ft_rewrite(existing_index, arg, data);
			else
				ft_add(arg, data);
			free_split(split);
		}
		i++;
	}
	return (0);
}
