/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kokot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:15:02 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 22:15:11 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_append(t_data *data, char *filename)
{
	data->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND
			| O_CLOEXEC, 0777);
}

void	ft_open_trunc(t_data *data, char *filename)
{
	data->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC
			| O_CLOEXEC, 0777);
}
