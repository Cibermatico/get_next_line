
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"   //togliere
//#include "get_next_line.h" //riattivare
# define BUFFER_SIZE 3500	//togliere

size_t	ft_strlcpy(char *dest, const char *src, size_t size) //TOGLIERE TUTTE LE FUNZIONI
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
size_t	ft_strlen(const char *str)

{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
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
	return (new);
}
char	*ft_strjoin(char const *s1, char const *s2)
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

static int	handle_remainder(char **container, char **remainder)
{
	size_t	remainder_len;
	size_t	i;
	char	*sub;

	remainder_len = ft_strlen(*remainder);
	i = 0;
	while (i < remainder_len && (*remainder)[i] != '\n')
		i++;
	sub = ft_substr(*remainder, 0, i + 1);
	*container = ft_strjoin(*container, sub);
	free(sub);
	if (i == remainder_len - 1)
	{
		free(*remainder);
		*remainder = NULL;
	}
	else
		*remainder = ft_substr(*remainder, i + 1, remainder_len - i - 1);
	return i < remainder_len;
}

static char	*main_logic(int fd, char **container, char **remainder, char **buffer)
{
	size_t chars;
	size_t i;

	while ((chars = read(fd, *buffer, BUFFER_SIZE)) > 0)
	 {
		i = 0;
		(*buffer)[chars] = '\0';
		while (i < chars)
		{
			if ((*buffer)[i] == '\n') {
				*remainder = ft_substr(*buffer, i + 1, chars - i - 1);
				*container = ft_strjoin(*container, ft_substr(*buffer, 0, i + 1));
				free(*buffer);
				return *container;
			}
			i++;
		}
		*container = ft_strjoin(*container, *buffer);
	}
	free(*buffer);	
	return *container;
}

char *get_next_line(int fd)
{
	char *container; 
	char *buffer;
	static char *remainder;
		
	container = "";
	buffer = (char *)malloc(BUFFER_SIZE + 1);	
	if (!buffer)
		return (NULL);
	if (remainder && (handle_remainder(&container, &remainder) == 1))
		return container;
	return main_logic(fd, &container, &remainder, &buffer);
}

int main(void) //togliere il main
{
	int	fd;
	
	fd = open("test.txt", O_CREAT | O_RDONLY);	
	for (size_t i = 0; i < 3; i++)	
		printf("%s",get_next_line(fd));
		/*puts("-------------------------");
		printf("%s",get_next_line(fd));
		puts("-------------------------");
		printf("%s",get_next_line(fd));
		puts("-------------------------");
		printf("%s",get_next_line(fd));*/
		
	close(fd);
	
	return 0;
}
