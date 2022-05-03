/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperez- <maperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:11:58 by maperez-          #+#    #+#             */
/*   Updated: 2022/05/03 13:08:06 by maperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *save)
{
	int		pos;
	char	*str;

	if (!save)
		return (NULL);
	while (save[pos] && save[pos] != '\n')
		pos++;
	str = (char *)malloc(sizeof(char) * (pos + 2));
	if (!str)
		return (NULL);
	pos = 0;
	while (save[pos] && save[pos] != '\n')
	{
		str[pos] = save[pos];
		pos++;
	}
	if (save[pos] == '\n')
	{
		str[pos] == '\n';
		pos++;
	}
	str[pos] = '\0';
	return (str);
}

char	*ft_save(char *save)
{
	char	*str;
	int		save_pos;
	int		str_pos;

	save_pos = 0;
	while (save[save_pos] && save[save_pos != '\n'])
		save_pos++;
	if (!str)
	{
		free(save);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(save) + 1 - save_pos));
	if (!str)
		return (NULL);
	save_pos++;
	str_pos = 0;
	while (save[save_pos])
		str[str_pos] = save[save_pos];
	str[str_pos] = '\0';
	free(save);
	return (str);
}

char	*ft_read_save(int fd, char *save)
{
	char	*str;
	int		bytes;

	str = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(save, '\n') && bytes != 0)
	{
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(str);
			return (NULL);
		}
		str[bytes] = '\0';
		save = ft_strjoin(save, str);
	}
	free(str);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_save(save);
	return (line);
}
