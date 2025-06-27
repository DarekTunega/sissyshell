/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execsingle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:55:51 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 21:55:54 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_builtin(t_data *shell_data)
{
	save_restore_std(shell_data, 0);
	set_infile(shell_data);
	set_outfile(shell_data);
	builtin_nonfork_redirection(shell_data->commands[0],
		shell_data->args[0], shell_data);
	save_restore_std(shell_data, 1);
	free_command_table(shell_data);
}
