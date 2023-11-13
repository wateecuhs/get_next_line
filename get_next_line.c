/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:56 by panger            #+#    #+#             */
/*   Updated: 2023/11/13 18:51:08 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000000
#endif


static char	*ft_strdupset(char const *s, int start, int stop)
{
	char			*trg;
	unsigned int	count;
	int				i;

	i = 0;
	count = 0;
	while (s[count])
		count++;
	trg = (char *)malloc((stop - start + 1) * sizeof(char));
	if (!trg)
		return (NULL);
	while (s[start] && start < stop)
	{
		trg[i] = s[start];
		i++;
		start++;
	}
	trg[i] = '\0';
	return (trg);
}

char	*cut_str(char *str)
{
	char	*ret;	

	if (ft_strchr(str, '\n') == -1)
	{
		ret = ft_strdup(str);
		return (ret);
	}
	else
	{
		//printf("Str is '%s' and strchr finds %d\n", str, ft_strchr(str, '\n'));
		fflush(stdout);
		ret = ft_strdupset(str, 0, ft_strchr(str, '\n') + 1);
		return (ret);
	}
}

char	*ft_strdup(const char *s)
{
	int		srclen;
	int		i;
	char	*dest;

	srclen = 0;
	if (!s)
		return (NULL);
	while (s[srclen])
		srclen++;
	i = 0;
	dest = (char *)malloc((srclen + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < srclen)
	{
		dest[i] = s[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_stradd(char *s1, char *s2, int size)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < size)
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

char *get_next_line(int fd)
{
	int				char_read;
	static char		buffer[BUFFER_SIZE + 1];
	char			*str;
	char			*temp;
	int				i;
	int				j;

	char_read = -1;
	str = NULL;
	if (buffer[0] != 0)
	{
		//printf("Non-void buffer '%s'\n", buffer);
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (!(buffer[i] == '\n' && buffer[i + 1] == '\0'))
		{
			i++;
			str = ft_stradd(str, &buffer[i], BUFFER_SIZE - i);
			j = 0;
			while (i < BUFFER_SIZE)
				buffer[j++] = buffer[i++];
			buffer[j] = '\0';
			//printf("str '%s'\n", str);
		}
	}
	while (ft_strchr(str, '\n') == -1 && char_read != 0)
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read == 0)
		{
			//printf("returned here");
			temp = cut_str(str);
			free(str);
			//printf ("temp '%s'\n", temp);
			buffer[0] = '\0';
			return (temp);
		}
		//printf("CR %d\n", char_read);
		if (char_read == -1)
			return (NULL);
		buffer[char_read] = '\0';
		//printf("String : %s \n", buffer);
		str = ft_stradd(str, buffer, char_read);
		if (!str)
			return (NULL);
		//printf("String : %s \n", str);
	}
	temp = cut_str(str);
	free(str);
	return (temp);
}

/* #include <stdio.h>
int	main(void)
{
	int fd;
	char *str2;
	int		i;

	i = 0;
	fd = open("./gnlTester/files/big_line_with_nl", O_RDWR);
	str2 = get_next_line(fd);
	printf("FINAL :%s", str2);
	while (str2 != NULL)
	{
		free(str2);
		str2 = get_next_line(fd);
		printf("FINAL %d:%s", i, str2);
		i++;
	}
	free(str2);
} */