/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:39:03 by panger            #+#    #+#             */
/*   Updated: 2023/11/14 10:59:18 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		ft_strlen(char *str);
int		ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strdupset(char const *s, int start, int stop);
char	*ft_strdup(const char *s);
char	*ft_stradd(char *s1, char *s2, int size);

#endif