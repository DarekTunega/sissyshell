/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:37 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 21:49:13 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit;

static char	**ms_create_env_copy(void)
{
	int		env_count;
	int		i;
	char	**new_env;

	env_count = 0;
	while (environ[env_count] != NULL)
		env_count++;
	new_env = (char **)malloc((env_count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	ms_reset_command_data(t_data *shell_data)
{
	shell_data->commands = NULL;
	shell_data->args = NULL;
	shell_data->redirs = NULL;
	shell_data->delimiter = NULL;
	shell_data->last_command = -1;
	shell_data->infile = -1;
	shell_data->outfile = -1;
	shell_data->saved_stdin = -1;
	shell_data->saved_stdout = -1;
}

void	ms_setup_shell_data(t_data *shell_data)
{
	int		shell_var_idx;
	char	*current_user;

	shell_var_idx = ft_checkforexisting("SHELL");
	ms_reset_command_data(shell_data);
	shell_data->minishell_env = ms_create_env_copy();
	environ = shell_data->minishell_env;
	(void)shell_var_idx;
	current_user = getenv("USER");
	if (!current_user)
		current_user = "user";
	shell_data->user_name = ft_strdup(current_user);
}

int	main(void)
{
	t_data	shell_data;

	ms_setup_shell_data(&shell_data);
	ft_setup_interactive_signals();
	while (1)
		ms_process_input(&shell_data);
	return (0);
}
