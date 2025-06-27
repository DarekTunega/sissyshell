/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:11:02 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/03 21:50:32 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_child(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("\033[96mheredoc>\033[0m ");
		if (!line || (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
				&& ft_strlen(line) == ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

static void	ft_heredoc_parent(int read_fd, int write_fd, pid_t pid)
{
	close(write_fd);
	dup2(read_fd, STDIN_FILENO);
	close(read_fd);
	waitpid(pid, NULL, 0);
}

void	ft_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
		ft_heredoc_child(fd[1], delimiter);
	else
		ft_heredoc_parent(fd[0], fd[1], pid);
}
