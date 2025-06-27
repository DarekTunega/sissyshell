/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:50:21 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 22:50:25 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnopathx_util(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strnstr(environ[i], "PATH", 4) != 0)
			break ;
		i++;
	}
	return (i);
}
