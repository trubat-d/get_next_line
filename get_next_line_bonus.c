/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trubat-d <trubat-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:50:59 by trubat-d          #+#    #+#             */
/*   Updated: 2022/10/13 18:10:49 by trubat-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_bufconnect(char *buffer, char *temp, int size)
{
	char	*result;
	int		i;
	int		buffer_size;

	buffer_size = 0 + (!(!buffer)) * ft_strlen(buffer);
	result = malloc((buffer_size + size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[buffer_size + size] = '\0';
	i = 0;
	while (i < buffer_size)
	{
		result[i] = buffer[i];
		i++;
	}
	i = 0;
	while (i < size)
	{
		result[buffer_size + i] = temp[i];
		i++;
	}
	free(buffer);
	return (result);
}

char	*ft_truncate(char *buffer)
{
	int		i;
	char	*result;
	int		size;

	if (!buffer)
		return (NULL);
	size = 0;
	while (buffer[size] != '\n' && buffer[size])
		size++;
	result = malloc((size +1 + 1 * sizeof(char)));
	if (!result)
		return (NULL);
	result[size +1] = '\0';
	i = 0;
	while (i < size +1)
	{
		result[i] = buffer[i];
		i++;
	}
	return (result);
}

char	*ft_getbufferend(char *buffer)
{
	int		i;
	char	*result;
	int		size;
	int		buffer_size;

	if (!buffer)
		return (NULL);
	buffer_size = ft_strlen(buffer);
	size = 0;
	while (buffer[size] != '\n' && buffer[size])
		size++;
	if (!buffer[size] || !buffer[size + 1])
		return (free(buffer), NULL);
	if (buffer[size] == '\n')
		size++;
	result = (char *)malloc((buffer_size - size + 1) * sizeof(char));
	if (!result)
		return (free(buffer), NULL);
	result[buffer_size - size] = '\0';
	i = -1;
	while (++i < (buffer_size - size))
		result[i] = buffer[size + i];
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	int			read_desc;
	char		*ret_line;
	char		*temp_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_read)
		return (NULL);
	read_desc = 1;
	while ((ft_strchr(buffer[fd], '\n') == NULL) && read_desc != 0)
	{
		read_desc = read(fd, temp_read, BUFFER_SIZE);
		if (read_desc <= 0)
			break ;
		temp_read[read_desc] = '\0';
		buffer[fd] = ft_bufconnect(buffer[fd], temp_read, BUFFER_SIZE);
	}
	free(temp_read);
	ret_line = ft_truncate(buffer[fd]);
	buffer[fd] = ft_getbufferend(buffer[fd]);
	return (ret_line);
}
