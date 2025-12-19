/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shapetit <shapetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:06:01 by shapetit          #+#    #+#             */
/*   Updated: 2025/11/25 14:13:24 by shapetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_all(int fd, char *stash)
{
	char	*buff;
	int		verrif;

	verrif = 1;
	while (verrif > 0)
	{
		buff = malloc(BUFFER_SIZE + 1 * sizeof(char));
		verrif = read(fd, buff, BUFFER_SIZE);
		if (verrif < 0)
			return (free (buff), NULL);
		if (!stash && verrif < 1)
			return (free(buff), NULL);
		buff[verrif] = 0;
		stash = ft_strjoin(stash, buff);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*ft_cut_end(char *stash)
{
	char	*n_line;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0')
		return (stash);
	i++;
	n_line = ft_calloc(i + 1, sizeof(char));
	while (y < i)
	{
		n_line[y] = stash[y];
		y++;
	}
	return (n_line);
}

char	*ft_get_end(char *stash)
{
	char	*n_stash;

	n_stash = ft_strdup(ft_strchr(stash, '\n') + 1);
	free (stash);
	if (n_stash[0] == 0)
		return (free(n_stash), NULL);
	return (n_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[4096];
	char		*temp;

	stash[fd] = ft_get_all(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	if (!ft_strchr(stash[fd], '\n'))
	{
		temp = ft_strdup(stash[fd]);
		free(stash[fd]);
		stash[fd] = NULL;
		return (temp);
	}
	line = ft_cut_end(stash[fd]);
	stash[fd] = ft_get_end(stash[fd]);
	return (line);
}
