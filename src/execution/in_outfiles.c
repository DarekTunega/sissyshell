/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:11:12 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 22:14:55 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_count(char **words, char *redir_frst, char *redir_scnd)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (words[++i] != NULL)
	{
		if ((ft_strncmp(words[i], redir_frst, ft_strlen(redir_frst) + 1) == 0)
			|| (ft_strncmp(words[i], redir_scnd, ft_strlen(redir_scnd) + 1)
				== 0))
			count++;
	}
	return (count);
}

void	tokenize_infile_heredoc(char **words, t_data *data)
{
	int	i;
	int	count;
	int	done;

	count = redir_count(words, "<", "<<");
	done = 0;
	i = -1;
	while (words[++i] != NULL)
	{
		if (ft_strncmp(words[i], "<", ft_strlen("<") + 1) == 0)
		{
			done ++;
			if (done == count && words[i + 1] != NULL)
				data->infile = open(words[i + 1], O_RDONLY | O_CLOEXEC, 0777);
		}
		else if (ft_strncmp(words[i], "<<", ft_strlen("<<") + 1) == 0)
		{
			done ++;
			if (done == count && words[i + 1] != NULL)
				data->delimiter = ft_strdup(words[i + 1]);
		}
	}
}

void	handle_append_redir(char **words, t_data *data, t_redir_state *state)
{
	if (words[state->i + 1] != NULL)
	{
		ft_open_append(data, words[state->i + 1]);
		state->done++;
		if (state->done < state->count)
			close(data->outfile);
	}
}

void	handle_trunc_redir(char **words, t_data *data, t_redir_state *state)
{
	if (words[state->i + 1] != NULL)
	{
		ft_open_trunc(data, words[state->i + 1]);
		state->done++;
		if (state->done < state->count)
			close(data->outfile);
	}
}

void	tokenize_outfile(char **words, t_data *data)
{
	t_redir_state	state;

	state.i = -1;
	state.done = 0;
	state.count = redir_count(words, ">", ">>");
	while (words[++state.i] != NULL)
	{
		if (ft_strncmp(words[state.i], ">>", 3) == 0)
			handle_append_redir(words, data, &state);
		else if (ft_strncmp(words[state.i], ">", 2) == 0)
			handle_trunc_redir(words, data, &state);
	}
}
