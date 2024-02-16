
#include <stdlib.h> 
#include <stdio.h>
#include "get_next_line.h" 

static int	handle_remainder(char **container, char **remainder)
{
	size_t	remainder_len;
	size_t	i;
	char	*sub;
	char	*temp;

	remainder_len = ft_strlen(*remainder);
	i = 0;
	while (i < remainder_len && (*remainder)[i] != '\n')
		i++;
	sub = ft_substr(*remainder, 0, i + 1, 0);
	temp = ft_strjoin(*container, sub);
	free(*container);
	free(sub);
	*container = ft_strdup(temp, 0);
	free(temp);
	if (i == remainder_len - 1)
	{
		free(*remainder);
		*remainder = NULL;
	}
	else
	{
		temp = ft_substr(*remainder, i + 1, remainder_len - i - 1, 0);
		free(*remainder);
		*remainder = ft_strdup(temp, 0);
		free(temp);
	}
	return (i < remainder_len);	
}

static void main_logic(int fd, char **container, char **remainder, char **buffer)
{
	size_t chars;
	size_t i;
	char	*temp;

	while ((chars = read(fd, *buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		/*if (chars == -1)
			return */
		(*buffer)[chars] = '\0';
		while (i < chars)
		{
			if ((*buffer)[i] == '\n')
			{
				free(*remainder);
				*remainder = ft_substr(*buffer, i + 1, chars - i - 1,0);
				temp = ft_strjoin(*container, ft_substr(*buffer, 0, i + 1,0));
				free(*container); // ATTENZIONE AL MALLOC IN SUBSTR 
				*container = ft_strdup(temp, 0);
				free(temp);
				free(*buffer);
				return ;
			}
			i++;
		}
		temp = ft_strjoin(*container, *buffer);
		free(*container);
		*container = ft_strdup(temp, 0);
		free(temp);
	}
	if (chars <= 0)		
		return ;
	//free(*buffer);   //se tolgo qui forse esplode
}

char *get_next_line(int fd)		// risolto il loop infinito con file vuoto
{
	char *container; 
	char *buffer;
	static char *remainder;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	container = ft_strdup("", 0);
	buffer = (char *) malloc(BUFFER_SIZE + 1);	
	if (!buffer)
		return (NULL);
	if (remainder && (handle_remainder(&container, &remainder) == 1))
		return container;	
	main_logic(fd, &container, &remainder, &buffer);	
	if (container[0] == '\0')
	{
		free(remainder);  // forse doppio free qui se il file e'vuoto
		if (buffer != NULL)
		 	free(buffer); //aggiunto il free qui
		return NULL;
	}
	return container; 
}

int main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31mFile not valid\033[0m\n");
		return (1);
	}
	str = malloc(BUFFER_SIZE + 1);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	
	return 0;
}