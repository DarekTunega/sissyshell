/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:25:47 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/03 23:40:23 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_is_rd_tk(char *token)
{
	if ((ft_strncmp(token, "<", ft_strlen("<") + 1) == 0))
		return (true);
	else if ((ft_strncmp(token, ">", ft_strlen(">") + 1) == 0))
		return (true);
	else if ((ft_strncmp(token, "<<", ft_strlen("<<") + 1) == 0))
		return (true);
	else if ((ft_strncmp(token, ">>", ft_strlen(">>") + 1) == 0))
		return (true);
	return (false);
}

int	ms_count_non_redir_tokens(char **token_array)
{
	int	idx;
	int	valid_count;

	idx = 0;
	valid_count = 0;
	while (token_array[idx] != NULL)
	{
		if (ms_is_rd_tk(token_array[idx]) == false)
			valid_count++;
		if (ms_is_rd_tk(token_array[idx]) == true
			&& token_array[idx + 1] != NULL)
			idx++;
		idx++;
	}
	return (valid_count);
}

char	**ms_filter_redirection_tokens(char **token_array)
{
	int		src_idx;
	int		dest_idx;
	int		token_count;
	char	**filtered_tokens;

	token_count = ms_count_non_redir_tokens(token_array);
	filtered_tokens = (char **)malloc(sizeof(char *) * (token_count + 1));
	src_idx = 0;
	dest_idx = 0;
	while (token_array[src_idx] != NULL)
	{
		if (ms_is_rd_tk(token_array[src_idx]) == false)
		{
			filtered_tokens[dest_idx] = ft_strdup(token_array[src_idx]);
			dest_idx++;
		}
		if (ms_is_rd_tk(token_array[src_idx]) == true
			&& token_array[src_idx + 1] != NULL)
			src_idx++;
		src_idx++;
	}
	filtered_tokens[dest_idx] = NULL;
	free_split(token_array);
	return (filtered_tokens);
}

bool	check_newline_error(char **token_array)
{
	int	i;

	i = 0;
	while (token_array[i] != NULL)
	{
		if (ms_is_rd_tk(token_array[i]))
		{
			if (token_array[i + 1] == NULL)
			{
				write(2, "minishell: syntax error near unexpected token "
					"`newline'\n", 57);
				g_exit = 2;
				return (false);
			}
		}
		i++;
	}
	return (true);
}

void	lexer(char **token_array, t_data *shell_data)
{
	if (!ms_validate_redirection_syntax(token_array))
	{
		free_split(token_array);
		return ;
	}
	tokenize_outfile(token_array, shell_data);
	tokenize_infile_heredoc(token_array, shell_data);
	token_array = ms_filter_redirection_tokens(token_array);
	tokenize_command(token_array, shell_data);
	ft_command_check(shell_data);
	shell_data->args = argument_parser(shell_data->commands,
			shell_data->args);
	free_split(token_array);
}
