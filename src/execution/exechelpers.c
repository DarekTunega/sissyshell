/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exechelpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:52:43 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 21:59:47 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_handle_system_error(const char *msg)
{
	perror(msg);
	exit(1);
}

void	wait_for_all_children(pid_t *pids, int n_child)
{
	int	i;
	int	current_status;
	int	final_status_code;

	i = 0;
	final_status_code = 0;
	if (n_child > 0)
		final_status_code = 1;
	while (i < n_child)
	{
		if (waitpid(pids[i], &current_status, 0) == -1)
			ms_handle_system_error("waitpid in wait_for_all_children");
		if (i == n_child - 1)
		{
			if (WIFEXITED(current_status))
				final_status_code = WEXITSTATUS(current_status);
			else if (WIFSIGNALED(current_status))
				final_status_code = 128 + WTERMSIG(current_status);
		}
		i++;
	}
	if (n_child > 0)
		g_exit = final_status_code;
}

static void	handle_child_output(t_data *s_data, t_pipe_data *pipe_data)
{
	close(pipe_data->pipe_fds[0]);
	if (s_data->outfile != -1)
	{
		set_outfile(s_data);
	}
	else
	{
		if (dup2(pipe_data->pipe_fds[1], STDOUT_FILENO) == -1)
			ms_handle_system_error("dup2 stdout to pipe in child");
	}
	close(pipe_data->pipe_fds[1]);
}

void	execute_child_in_pipeline(t_data *s_data, int c_idx,
		t_pipe_data *pipe_data)
{
	ft_setup_child_signals();
	if (pipe_data->pipe_fd_read != STDIN_FILENO)
	{
		if (dup2(pipe_data->pipe_fd_read, STDIN_FILENO) == -1)
			ms_handle_system_error("dup2 stdin in child");
		close(pipe_data->pipe_fd_read);
	}
	if (!pipe_data->is_last_cmd)
		handle_child_output(s_data, pipe_data);
	else
		set_outfile(s_data);
	ms_execute_single_command(s_data->commands[c_idx], c_idx, s_data);
	exit(EXIT_FAILURE);
}

void	manage_parent_pipes_for_next_iteration(int *p_fd_r_io,
		int *cur_pipe_fds, bool pipe_was_created)
{
	if (*p_fd_r_io != STDIN_FILENO)
		close(*p_fd_r_io);
	if (pipe_was_created)
	{
		close(cur_pipe_fds[1]);
		*p_fd_r_io = cur_pipe_fds[0];
	}
}

void	setup_pipe_and_fork(t_executor_state *s)
{
	if (!s->is_last_cmd)
	{
		if (pipe(s->pipe_fds) == -1)
			ms_handle_system_error("pipe in executor loop");
	}
	s->pids[s->num_children] = fork();
	if (s->pids[s->num_children] == -1)
	{
		if (!s->is_last_cmd)
		{
			close(s->pipe_fds[0]);
			close(s->pipe_fds[1]);
		}
		ms_handle_system_error("fork in executor loop");
	}
}
