/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:30:14 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 22:30:20 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_args(char **arr_src, char *command)
{
	char	**arr_dst;
	int		i;
	int		counter;

	counter = 0;
	i = 0;
	while (arr_src[counter])
		counter++;
	counter += 2;
	arr_dst = (char **)malloc(sizeof(char *) * (counter));
	arr_dst[i] = ft_strdup(command);
	if (!arr_dst)
		return (NULL);
	while (i < counter - 1)
	{
		arr_dst[i + 1] = arr_src[i];
		i++;
	}
	arr_dst[i] = NULL;
	free(arr_src);
	return (arr_dst);
}

char	***argument_parser(char **commands, char ***args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		args[i] = copy_args(args[i], commands[i]);
		i++;
	}
	return (args);
}

void	tokenize_arg(char **token_array, t_data *shell_data, int cmd_count)
{
	int		token_idx;
	int		cmd_idx;
	char	***argument_arrays;

	token_idx = 0;
	cmd_idx = 0;
	argument_arrays = allocate_argument_arrays(cmd_count);
	while (token_array[token_idx] != NULL)
	{
		process_single_command_args(argument_arrays, token_array, &token_idx,
			cmd_idx);
		cmd_idx++;
		if (token_array[token_idx] == NULL)
			break ;
		token_idx++;
	}
	argument_arrays[cmd_idx] = NULL;
	shell_data->args = argument_arrays;
}
