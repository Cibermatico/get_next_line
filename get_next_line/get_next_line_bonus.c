/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsquarci <lsquarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:32:23 by lsquarci          #+#    #+#             */
/*   Updated: 2024/02/17 17:07:23 by lsquarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> 
#include <stdio.h>
#include "get_next_line.h" 

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;
	size_t	i;

	count = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[count] != '\0')
		++count;
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (count);
}

static char	*join_free(char *str1, char *str2)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(str1, str2);
	result = ft_strdup(temp, 0);
	free(temp);
	free(str1);
	return (result);
}

static int	find_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static char	*read_line(int fd, char *remainder)
{
	char	*buffer;
	int		chars;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (!ft_strchr(remainder, '\n'))
	{
		chars = read(fd, buffer, BUFFER_SIZE);
		if (chars == 0 || chars == -1)
			break ;
		buffer[chars] = '\0';
		remainder = join_free(remainder, buffer);
	}
	free (buffer);
	if (ft_strlen(remainder) == 0)
	{
		free(remainder);
		return (NULL);
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[257];
	char		*container;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder[fd])
		remainder[fd] = ft_strdup("", 0);
	remainder[fd] = read_line(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	container = ft_substr(remainder[fd], 0, find_nl(remainder[fd]) + 1, 0);
	remainder[fd] = ft_substr(remainder[fd], find_nl(remainder[fd]) + 1,
			ft_strlen(remainder[fd]), 1);
	return (container);
}
