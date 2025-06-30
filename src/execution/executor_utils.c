/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:11:07 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/02 22:53:13 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_outfile(t_data *data)
{
	if (data->outfile != -1)
	{
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
}

void	set_infile(t_data *data)
{
	if (data->infile != -1)
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	else if (data->delimiter != NULL)
		ft_heredoc(data->delimiter);
}

void	save_restore_std(t_data *data, int i)
{
	if (i == 0)
	{
		data->saved_stdin = dup(STDIN_FILENO);
		if (data->saved_stdin == -1)
		{
			perror("minishell: dup failed for saved_stdin");
		}
		data->saved_stdout = dup(STDOUT_FILENO);
		if (data->saved_stdout == -1)
		{
			perror("minishell: dup failed for saved_stdout");
		}
	}
	else if (i == 1)
	{
		dup2(data->saved_stdout, STDOUT_FILENO);
		dup2(data->saved_stdin, STDIN_FILENO);
		close(data->saved_stdin);
		close(data->saved_stdout);
	}
}

static void	ms_handle_system_error(const char *msg)
{
	perror(msg);
	exit(1);
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
