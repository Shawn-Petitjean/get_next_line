/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shapetit <shapetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:35:27 by shapetit          #+#    #+#             */
/*   Updated: 2025/11/25 14:30:57 by shapetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*stash;
	char		*temp;

	stash = ft_get_all(fd, stash);
	if (!stash)
		return (NULL);
	if (!ft_strchr(stash, '\n'))
	{
		temp = ft_strdup(stash);
		free(stash);
		stash = NULL;
		return (temp);
	}
	line = ft_cut_end(stash);
	stash = ft_get_end(stash);
	return (line);
}
