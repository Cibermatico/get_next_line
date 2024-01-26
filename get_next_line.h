
#ifndef GET_NEXT_LINE_H
	# define GET_NEXT_LINE_H

	# include <stdlib.h>

	# ifndef BUFFER_SIZE
		#  define BUFFER_SIZE 1000
	# endif

	size_t	ft_strlcpy(char *dest, const char *src, size_t size);
	char	*get_next_line(int fd);
	size_t	ft_strlen(const char *str);
	char	*ft_substr(char const *s, unsigned int start, size_t len);
	char	*ft_strjoin(char const *s1, char const *s2);
	
# endif