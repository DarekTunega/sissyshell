/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skvackov <skvackov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:30:00 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/03 22:50:00 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***allocate_argument_arrays(int cmd_count)
{
	return ((char ***)malloc(sizeof(char **) * (cmd_count + 1)));
}

void	allocate_single_command_args(char ***argument_arrays, int cmd_idx,
		int arg_count)
{
	if (arg_count == 0)
		argument_arrays[cmd_idx] = (char **)malloc(sizeof(char *) * (2));
	else
		argument_arrays[cmd_idx] = (char **)malloc(sizeof(char *)
				* (arg_count + 1));
}

void	process_single_command_args(char ***argument_arrays,
		char **token_array, int *token_idx, int cmd_idx)
{
	int	arg_count;

	arg_count = ms_count_command_args(token_array, *token_idx);
	allocate_single_command_args(argument_arrays, cmd_idx, arg_count);
	if (token_array[*token_idx] != NULL)
		(*token_idx)++;
	ms_fill_command_arguments(argument_arrays, token_array, token_idx,
		cmd_idx);
}

int	ms_count_command_args(char **token_array, int start_idx)
{
	int	arg_count;

	arg_count = 0;
	if (token_array[start_idx] != NULL)
		start_idx++;
	while (token_array[start_idx] != NULL
		&& !ms_is_pipe_operator(token_array[start_idx]))
	{
		arg_count++;
		start_idx++;
	}
	return (arg_count);
}

void	ms_fill_command_arguments(char ***args, char **token_array,
		int *token_idx, int cmd_idx)
{
	int	arg_idx;

	arg_idx = 0;
	while (token_array[*token_idx] != NULL
		&& !ms_is_pipe_operator(token_array[*token_idx]))
	{
		args[cmd_idx][arg_idx] = ft_strdup(token_array[*token_idx]);
		arg_idx++;
		(*token_idx)++;
	}
	args[cmd_idx][arg_idx] = NULL;
}
