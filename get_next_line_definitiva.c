
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

static int	handle_remainder(char **container, char **remainder)
{
	size_t	remainder_len = ft_strlen(*remainder);
	size_t	i;
	char	*sub;

	i = 0;
	while (i < remainder_len)
	{
		if ((*remainder)[i] == '\n')
		{
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
			return 1;
		}
		i++;
	}
	*container = ft_strjoin(*container, *remainder);
	free(*remainder);
	*remainder = NULL;
	return (0); //occhio
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
	if (remainder && (handle_remainder(&container, &remainder) == 1))
		return container;
	return main_logic(fd, &container, &remainder, &buffer);
}


int main(void)
{
	int		fd;
	
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
