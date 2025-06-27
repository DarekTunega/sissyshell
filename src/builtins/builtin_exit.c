/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:06:18 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 19:06:30 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ms_validate_numeric_arg(char *argument)
{
	int	char_idx;

	char_idx = 0;
	if (!argument || !argument[0])
		return (false);
	if (argument[char_idx] == '-' || argument[char_idx] == '+')
		char_idx++;
	if (!argument[char_idx])
		return (false);
	while (argument[char_idx] != '\0')
	{
		if (argument[char_idx] < '0' || argument[char_idx] > '9')
			return (false);
		char_idx++;
	}
	return (true);
}

static void	ms_exit_with_single_arg(t_data *shell_data)
{
	int	exit_code;

	if ((ms_validate_numeric_arg(shell_data->args[0][1]) == true))
	{
		exit_code = ft_atoi(shell_data->args[0][1]);
		exit_code = ((exit_code % 256) + 256) % 256;
		free_command_table(shell_data);
		free_split(shell_data->minishell_env);
		exit(exit_code);
	}
	else if (ms_validate_numeric_arg(shell_data->args[0][1]) == false)
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: ", 18);
		write(2, shell_data->args[0][1],
			ft_strlen(shell_data->args[0][1]));
		write(2, ": numeric argument required\n", 29);
		free_command_table(shell_data);
		free_split(shell_data->minishell_env);
		exit(2);
	}
}

static void	ms_output_numeric_error(t_data *shell_data)
{
	write(2, "exit\n", 5);
	write(2, "minishell: exit: ", 18);
	write(2, shell_data->args[0][1],
		ft_strlen(shell_data->args[0][1]));
	write(2, ": numeric argument required\n", 29);
}

void	ft_exit(t_data *shell_data)
{
	if (shell_data->args[0][1] && !(shell_data->args[0][2]))
		ms_exit_with_single_arg(shell_data);
	else if (shell_data->args[0][1] && shell_data->args[0][2])
	{
		if (ms_validate_numeric_arg(shell_data->args[0][1]) == false)
		{
			ms_output_numeric_error(shell_data);
			free_command_table(shell_data);
			free_split(shell_data->minishell_env);
			exit(2);
		}
		else
		{
			write(2, "exit\nminishell: exit: too many arguments\n",
				42);
			g_exit = 1 << 8;
		}
	}
	else
	{
		free_command_table(shell_data);
		free_split(shell_data->minishell_env);
		write(1, "exit\n", 5);
		exit(0);
	}
}
