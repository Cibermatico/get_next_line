
#ifndef GET_NEXT_LINE_H
	# define GET_NEXT_LINE_H

	# include <stdlib.h>
	# include <unistd.h>
	# include <fcntl.h>

	# ifndef BUFFER_SIZE
		#  define BUFFER_SIZE 1
	# endif

	size_t	ft_strlcpy(char *dest, const char *src, size_t size);
	char	*get_next_line(int fd);
	size_t	ft_strlen(const char *str);
	char	*ft_substr(char *s, unsigned int start, size_t len, short want2befreed);
	char	*ft_strjoin(char *s1, char *s2);
	char	*ft_strdup(char *src, short want2befreed);
	
# endif