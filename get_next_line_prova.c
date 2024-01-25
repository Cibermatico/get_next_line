#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

# define BUFFER_SIZE 9999

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == c)
			return ((char *)&str[len]);
		else
			len--;
	}
	return (NULL);
}
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)s;
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}
void	*ft_calloc(size_t count, size_t size)
{
	void			*output;
	unsigned int	total;

	total = count * size;
	output = malloc(total);
	if (!output)
		return (NULL);
	ft_bzero(output, total);
	return (output);
}
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
char	*ft_strdup(const char *src)
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
	return (copy);
}

char *get_next_line(int fd)
{
    static char *container;
    char *buffer;
    char *sub;
    static char *remainder;

    size_t chars;
    size_t i;
	container = NULL;
    if (container == NULL)
        container = ft_strdup("");

    buffer = (char *)malloc(BUFFER_SIZE + 1);
    sub = (char *)malloc(BUFFER_SIZE + 1);

    if (remainder)
    {
        size_t remainder_len = strlen(remainder);
        for (i = 0; i < remainder_len; i++)
        {
            if (remainder[i] == '\n')
            {
                sub = ft_substr(remainder, 0, i + 1);
                container = ft_strjoin(container, sub);
                free(sub);

                // Se il remainder contiene solo '\n', allora non è rimasta nessuna parte di riga
                if (i == remainder_len - 1)
                {
                    free(remainder);
                    remainder = NULL;
                }
                else
                {
                    remainder = ft_substr(remainder, i + 1, remainder_len - i - 1);
                }

                return container;
            }
        }
        // Se non troviamo '\n' nel remainder, aggiungi l'intero remainder a container
        container = ft_strjoin(container, remainder);
        free(remainder);
        remainder = NULL;
    }

    while ((chars = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        i = 0;
        buffer[chars] = '\0';

        while (i < chars)
        {
            if (buffer[i] == '\n')
            {
                sub = ft_substr(buffer, 0, i + 1);
                remainder = ft_substr(buffer, i + 1, chars - i - 1);
                container = ft_strjoin(container, sub);
                free(sub);
                free(buffer);
                return container;
            }
            i++;
        }

        container = ft_strjoin(container, buffer);
    }

    free(buffer);
    return container;
}


int main(void)
{
	char	*res;
	int		fd;
	size_t	chars;

	fd = open("test.txt", O_CREAT | O_RDONLY);	
	for (size_t i = 0; i < 4; i++)	
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