/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shapetit <shapetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:37:26 by shapetit          #+#    #+#             */
/*   Updated: 2025/11/24 18:18:31 by shapetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc( size_t n, size_t l)
{
	unsigned char	*a;
	size_t			i;

	if (!n || !l)
		return (malloc(0));
	if (n > 2147483647 || l > 2147483647)
		return (NULL);
	a = malloc(n * l);
	if (!a)
		return (NULL);
	i = 0;
	while (i < n)
	{
		a[i] = 0;
		i++;
	}
	return (a);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	dest = malloc((1 + i) * sizeof(char));
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		y;
	char	*line;
	int		len_s;

	i = 0;
	y = -1;
	if (s1 == NULL)
		len_s = 0;
	else
		len_s = ft_strlen(s1);
	line = ft_calloc((len_s + ft_strlen(s2) + 1), sizeof(char));
	if (!line)
		return (NULL);
	while (++y < len_s)
	{
		line[y] = s1[y];
	}
	while (s2[i] != '\0')
	{
		line[y + i] = s2[i];
		i++;
	}
	line[i + y] = '\0';
	return (free(s1), free(s2), line);
}
