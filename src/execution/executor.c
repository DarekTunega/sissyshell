/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:10:15 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/03 21:55:38 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_execute_single_command(char *cmd_path, int cmd_position,
		t_data *shell_data)
{
	if (ft_is_builtin(cmd_path))
		builtin_redirection_fork(cmd_path, shell_data->args[cmd_position],
			shell_data);
	else
	{
		if (execve(cmd_path, shell_data->args[cmd_position], environ) == -1)
		{
			write(2, "minishell: Command not found: ", 31);
			write(2, cmd_path, ft_strlen(cmd_path));
			write(2, "\n", 1);
			free_command_table(shell_data);
			free_split(shell_data->minishell_env);
			exit(127);
		}
	}
}

static void	handle_child_process(t_executor_state *s)
{
	t_pipe_data	pipe_data;

	pipe_data.pipe_fd_read = s->prev_fd_read;
	pipe_data.pipe_fds = s->pipe_fds;
	pipe_data.is_last_cmd = s->is_last_cmd;
	execute_child_in_pipeline(s->shell_data, s->cmd_idx, &pipe_data);
}

static void	process_pipeline_commands(t_executor_state *s)
{
	while (s->cmd_idx <= s->shell_data->last_command)
	{
		s->is_last_cmd = (s->cmd_idx == s->shell_data->last_command);
		setup_pipe_and_fork(s);
		if (s->pids[s->num_children] == 0)
			handle_child_process(s);
		manage_parent_pipes_for_next_iteration(&(s->prev_fd_read),
			s->pipe_fds, !s->is_last_cmd);
		s->num_children++;
		s->cmd_idx++;
	}
	if (s->prev_fd_read != STDIN_FILENO)
		close(s->prev_fd_read);
}

static void	execute_pipeline(t_data *shell_data)
{
	t_executor_state	state;

	state.cmd_idx = 0;
	state.num_children = 0;
	state.prev_fd_read = STDIN_FILENO;
	state.shell_data = shell_data;
	save_restore_std(shell_data, 0);
	process_pipeline_commands(&state);
	wait_for_all_children(state.pids, state.num_children);
	save_restore_std(shell_data, 1);
	free_command_table(shell_data);
}

void	ft_executor(t_data *shell_data)
{
	if (shell_data->last_command < 0)
		return ;
	if (shell_data->last_command == 0 && ft_is_builtin(shell_data->commands[0]))
		execute_single_builtin(shell_data);
	else
		execute_pipeline(shell_data);
}
