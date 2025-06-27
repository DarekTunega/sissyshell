/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:50:42 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 22:50:44 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen("echo") + 1) == 0)
		return (true);
	else if (ft_strncmp(command, "pwd", ft_strlen("pwd") + 1) == 0)
		return (true);
	else if (ft_strncmp(command, "cd", ft_strlen("cd") + 1) == 0)
		return (true);
	else if (ft_strncmp(command, "env", ft_strlen("env") + 1) == 0)
		return (true);
	else if (ft_strncmp(command, "export", ft_strlen("export") + 1) == 0)
		return (true);
	else if (ft_strncmp(command, "unset", ft_strlen("unset") + 1) == 0)
		return (true);
	else if (ft_strncmp(command, "exit", ft_strlen("exit") + 1) == 0)
		return (true);
	else
		return (false);
}

bool	ft_is_pathx(char *command)
{
	int	test;

	test = access(command, X_OK);
	if (test == 0)
		return (true);
	else
		return (false);
}

bool	ft_isnopathx(char *command)
{
	char	**paths;
	char	*path;
	char	*with_slash;
	int		i;

	i = ft_isnopathx_util();
	if (environ[i] == NULL)
		return (false);
	paths = ft_split(environ[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		with_slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(with_slash, command);
		free(with_slash);
		if (access(path, X_OK) == 0)
		{
			free_split(paths);
			return (free(path), true);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (false);
}

char	*ft_return_path(char *command)
{
	char	**paths;
	char	*path;
	char	*with_slash;
	int		i;

	i = ft_isnopathx_util();
	if (environ[i] == NULL)
		return (NULL);
	paths = ft_split(environ[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		with_slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(with_slash, command);
		free(with_slash);
		if (access(path, X_OK) == 0)
		{
			free(command);
			return (free_split(paths), path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	ft_command_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->commands[i] != NULL)
	{
		if (ft_is_builtin(data->commands[i]) == true)
			i++;
		else if (ft_is_pathx(data->commands[i]) == true)
			i++;
		else if (ft_isnopathx(data->commands[i]) == true)
			data->commands[i] = ft_return_path(data->commands[i]);
		else
			break ;
	}
}
