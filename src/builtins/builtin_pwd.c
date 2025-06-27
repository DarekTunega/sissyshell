/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:00:00 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 19:08:27 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd_fork(char **args, t_data *data)
{
	char	cwd[MAX_PATH_LENGTH];

	(void) args;
	if (getcwd(cwd, MAX_PATH_LENGTH) != NULL)
		printf("%s\n", cwd);
	fork_exit(0, data);
}

int	ft_pwd_nonfork(char **args)
{
	char	cwd[MAX_PATH_LENGTH];

	(void) args;
	if (getcwd(cwd, MAX_PATH_LENGTH) != NULL)
		printf("%s\n", cwd);
	return (0);
}
