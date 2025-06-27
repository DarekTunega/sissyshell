/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:22:00 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 21:48:36 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_get_user_input(t_data *shell_data)
{
	char	*user_input;
	char	*shell_prompt;

	shell_prompt = ft_strjoin(shell_data->user_name, "@minishell>> ");
	user_input = readline(shell_prompt);
	free(shell_prompt);
	if (user_input == NULL)
	{
		write(1, "exit\n", 5);
		free(shell_data->user_name);
		exit(0);
	}
	return (user_input);
}

static void	ms_execute_command(char *user_input, t_data *shell_data)
{
	add_history(user_input);
	ms_reset_command_data(shell_data);
	ft_parser(user_input, shell_data);
	if (shell_data->commands != NULL)
	{
		shell_data->last_command = commands_counting(shell_data->commands) - 1;
		if (shell_data->last_command >= 0)
			ft_executor(shell_data);
	}
}

void	ms_process_input(t_data *shell_data)
{
	char	*user_input;

	user_input = ms_get_user_input(shell_data);
	if (user_input[0] != '\0')
		ms_execute_command(user_input, shell_data);
	free(user_input);
}
