/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skvackov <skvackov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:30:26 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/03 22:50:00 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_valid_command(char *token)
{
	if (ft_strncmp(token, "echo", ft_strlen("echo") + 1) == 0)
		return (1);
	else if (ft_strncmp(token, "pwd", ft_strlen("pwd") + 1) == 0)
		return (1);
	else if (ft_strncmp(token, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	else if (ft_strncmp(token, "env", ft_strlen("env") + 1) == 0)
		return (1);
	else if (ft_strncmp(token, "export", ft_strlen("export") + 1) == 0)
		return (1);
	else if (ft_strncmp(token, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	else if (ft_strncmp(token, "clear", ft_strlen("clear") + 1) == 0)
		return (1);
	else if (ft_strncmp(token, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	else if (ft_strchr(token, '/') != NULL)
		return (1);
	return (0);
}

static int	ms_count_commands_in_pipeline(char **token_array)
{
	int	idk;
	int	cmd_count;

	idk = 0;
	cmd_count = 0;
	if (token_array != NULL)
	{
		while (token_array[idk] != NULL)
		{
			cmd_count++;
			idk++;
			if (token_array[idk] != NULL)
			{
				while (token_array[idk] != NULL
					&& !ms_is_pipe_operator(token_array[idk]))
					idk++;
				if (token_array[idk] != NULL)
				{
					if (ft_strncmp(token_array[idk], "|", 2) == 0)
						idk++;
				}
			}
		}
	}
	return (cmd_count);
}

static int	ms_advance_to_next_command(char **token_array, int current_idk)
{
	while (token_array[current_idk] != NULL
		&& !ms_is_pipe_operator(token_array[current_idk]))
		current_idk++;
	if (token_array[current_idk] != NULL)
	{
		if (ms_is_pipe_operator(token_array[current_idk]))
			current_idk++;
	}
	return (current_idk);
}

void	tokenize_command(char **token_array, t_data *shell_data)
{
	int		token_idk;
	int		cmd_idk;
	int		command_count;
	char	**command_list;

	command_count = ms_count_commands_in_pipeline(token_array);
	command_list = (char **)malloc(sizeof(char *) * (command_count + 1));
	token_idk = 0;
	cmd_idk = 0;
	if (token_array != NULL)
	{
		while (token_array[token_idk] != NULL)
		{
			command_list[cmd_idk++] = ft_strdup(token_array[token_idk++]);
			if (token_array[token_idk] != NULL)
				token_idk = ms_advance_to_next_command(token_array, token_idk);
		}
		command_list[cmd_idk] = NULL;
	}
	shell_data->commands = command_list;
	tokenize_arg(token_array, shell_data, command_count);
}

bool	ms_is_pipe_operator(char *token)
{
	if (ft_strncmp(token, "|", 2) == 0)
		return (true);
	else
		return (false);
}
