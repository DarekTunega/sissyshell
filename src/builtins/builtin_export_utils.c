/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:06:51 by skvackov          #+#    #+#             */
/*   Updated: 2025/06/02 19:07:06 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkforexisting(char *var)
{
	int		i;
	char	**split;

	i = 0;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (ft_strncmp(split[0], var, ft_strlen(var)) == 0)
		{
			free_split(split);
			return (i);
		}
		else
			free_split(split);
		i++;
	}
	return (-1);
}

char	*ft_checkarg(char *arg)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!ft_isalpha(arg[i]))
		return (NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			flag++;
		i++;
	}
	i = -1;
	while (arg[++i] != '=')
		if ((!ft_isalnum(arg[i])) && arg[i] != '_')
			return (NULL);
	if (flag == 0)
		return (NULL);
	else if (flag == 1 && arg[0] != '=' && arg[i - 1] != '=')
		return (arg);
	else
		return (NULL);
}
