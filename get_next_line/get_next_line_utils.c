/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsquarci <lsquarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:41:23 by lsquarci          #+#    #+#             */
/*   Updated: 2024/02/17 16:41:23 by lsquarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)

{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len, short want2befreed)
{
	char	*new;
	size_t	len1;
	size_t	finish;

	if (!s)
		return (NULL);
	len1 = ft_strlen(s);
	finish = 0;
	if (start < len1)
		finish = len1 - start;
	if (finish > len)
		finish = len;
	new = (char *)malloc(sizeof(char) * (finish + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s + start, finish + 1);
	if (want2befreed == 1)
		free(s);
	return (new);
}

char	*ft_strchr(const char *str, int c)
{
	while ((*str != '\0') && (*str != (char)c))
	{
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return ((char *)(NULL));
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*result;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (result == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			result[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			result[len1] = s2[i];
			len1++;
		}
		result[len1] = '\0';
		return (result);
	}
	return (NULL);
}

char	*ft_strdup(char *src, short want2befreed)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	copy = (char *)malloc(i * sizeof(char) + 1);
	if (!copy)
		return (NULL);
	while (j <= i)
	{
		copy[j] = src[j];
		j++;
	}
	copy[i] = '\0';
	if (want2befreed == 1)
		free(src);
	return (copy);
}
