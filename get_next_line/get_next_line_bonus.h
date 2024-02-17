/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsquarci <lsquarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:02:03 by lsquarci          #+#    #+#             */
/*   Updated: 2024/02/17 17:02:03 by lsquarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_substr(char *s, unsigned int start, size_t len, short want2befreed);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src, short want2befreed);
char	*ft_strchr(const char *str, int c);
#endif