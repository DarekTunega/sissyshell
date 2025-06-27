/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:05:25 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 21:50:15 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_env(char *var, char *value)
{
	char	*temp_value;
	char	*result;
	int		i;
	int		j;
	int		len;

	i = -1;
	j = 0;
	len = ft_strlen(var) + ft_strlen(value) + 2;
	temp_value = ft_strdup(value);
	result = malloc(len);
	if (!result || !temp_value)
		return (NULL);
	while (++i < (int)ft_strlen(var))
		result[i] = var[i];
	result[i++] = '=';
	while (j < (int)ft_strlen(temp_value))
		result[i++] = temp_value[j++];
	result[i] = '\0';
	free(temp_value);
	return (result);
}

static void	ft_errorandexit(char *arg, t_data *data)
{
	printf("cd: %s: no such file or directory.\n", arg);
	fork_exit(1, data);
}

void	ft_cd_fork(char **args, t_data *data)
{
	int		argument_count;
	char	old_pwd[MAX_PATH_LENGTH];
	char	cwd[MAX_PATH_LENGTH];

	argument_count = commands_counting(args);
	if (argument_count > 2)
	{
		printf("cd: too many arguments\n");
		fork_exit(1, data);
	}
	else
	{
		getcwd(old_pwd, MAX_PATH_LENGTH);
		if (argument_count == 1)
			chdir(getenv("HOME"));
		else if (args[1][0] == '-')
			chdir(getenv("OLDPWD"));
		else if (chdir(args[1]) == -1)
			ft_errorandexit(args[1], data);
		getcwd(cwd, MAX_PATH_LENGTH);
		ft_rewrite(ft_checkforexisting("PWD"), join_env("PWD", cwd), data);
		ft_rewrite(ft_checkforexisting("OLDPWD"),
			join_env("OLDPWD", old_pwd), data);
	}
	fork_exit(0, data);
}

int	ft_cd_nonfork(char **args, t_data *data)
{
	int		argument_count;
	char	old_pwd[MAX_PATH_LENGTH];
	char	cwd[MAX_PATH_LENGTH];

	argument_count = commands_counting(args);
	if (argument_count > 2)
		return (printf("cd: too many arguments\n"), 256);
	else
	{
		getcwd(old_pwd, MAX_PATH_LENGTH);
		if (argument_count == 1)
			chdir(getenv("HOME"));
		else if (args[1][0] == '-')
			chdir(getenv("OLDPWD"));
		else if (chdir(args[1]) == -1)
			return (printf("cd: %s: no such file or directory.\n",
					args[1]), 256);
		getcwd(cwd, MAX_PATH_LENGTH);
		ft_rewrite(ft_checkforexisting("PWD"), join_env("PWD", cwd), data);
		ft_rewrite(ft_checkforexisting("OLDPWD"),
			join_env("OLDPWD", old_pwd), data);
	}
	return (0);
}
