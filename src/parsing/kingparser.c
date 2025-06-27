/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kingparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:29:00 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/03 23:39:31 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(const char *user_input, t_data *shell_data)
{
	char	**token_array;

	token_array = ft_split(prepare_quoted_string(user_input), 29);
	token_array = replace_env_var_nonquated(token_array);
	token_array = parse_quated_strings(token_array);
	token_array = status_var_check(token_array);
	lexer(token_array, shell_data);
}

bool	check_consecutive_redirs(char **token_array)
{
	int	i;

	i = 0;
	while (token_array[i] != NULL)
	{
		if (ms_is_rd_tk(token_array[i]))
		{
			if (token_array[i + 1] != NULL && ms_is_rd_tk(token_array[i + 1]))
			{
				write(2, "minishell: syntax error near unexpected token `",
					48);
				write(2, token_array[i + 1], ft_strlen(token_array[i + 1]));
				write(2, "'\n", 2);
				g_exit = 2;
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	ms_validate_redirection_syntax(char **token_array)
{
	if (!check_newline_error(token_array))
		return (false);
	if (!check_consecutive_redirs(token_array))
		return (false);
	return (true);
}
