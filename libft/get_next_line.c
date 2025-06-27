/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunega <dtunega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:51:50 by dtunega           #+#    #+#             */
/*   Updated: 2025/06/02 17:27:25 by dtunega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}

char	*set_line_buffer(int fd, char *left, char *buffer)
{
	ssize_t	bread;
	char	*temp;

	bread = 1;
	while (bread > 0)
	{
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread == -1)
		{
			free(left);
			return (NULL);
		}
		else if (bread == 0)
			break ;
		buffer[bread] = 0;
		if (!left)
			left = ft_strdup("");
		temp = left;
		left = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left);
}

char	*set_line(char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	temp = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*temp == 0)
	{
		free(temp);
		temp = NULL;
	}
	line[i + 1] = 0;
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*left;
	char		*line;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 256)
	{
		free(buffer);
		free(left);
		buffer = NULL;
		left = NULL;
		return (NULL);
	}
	line = set_line_buffer(fd, left, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left = set_line(line);
	return (line);
}
