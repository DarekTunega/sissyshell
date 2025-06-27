/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:08:35 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 19:09:48 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delenv(int index, t_data *data)
{
	char	**new_environ;
	int		size;
	int		i;
	int		j;

	size = 0;
	i = 0;
	j = 0;
	while (environ[size] != NULL)
		size++;
	new_environ = malloc((size) * sizeof(char *));
	while (i < size)
	{
		if (i != index)
		{
			new_environ[j] = ft_strdup(environ[i]);
			j++;
		}
		i++;
	}
	new_environ[j] = NULL;
	free_split(data->minishell_env);
	data->minishell_env = new_environ;
	environ = new_environ;
}

void	ft_unset_fork(char **words, t_data *data)
{
	int	i;
	int	index;

	i = 1;
	while (words[i] != NULL)
	{
		index = ft_checkforexisting(words[i]);
		if (index != -1)
			ft_delenv(index, data);
		i++;
	}
	fork_exit(0, data);
}

int	ft_unset_nonfork(char **words, t_data *data)
{
	int	i;
	int	index;

	i = 1;
	while (words[i] != NULL)
	{
		index = ft_checkforexisting(words[i]);
		if (index != -1)
			ft_delenv(index, data);
		i++;
	}
	return (0);
}
