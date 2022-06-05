/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:07:28 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:08:09 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_to_full(int fd, char *full)
{
	char		*buff;
	int			rd_b;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	rd_b = 1;
	while (!ft_strchr_gnl(full, '\n') && rd_b != 0)
	{
		rd_b = read(fd, buff, BUFFER_SIZE);
		if (rd_b == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_b] = '\0';
		full = ft_strjoin_gnl(full, buff);
	}
	free(buff);
	return (full);
}

char	*get_next_line(int fd)
{
	static char		*full;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	full = read_to_full(fd, full);
	if (!full)
		return (NULL);
	line = ft_strdup_gnl(full);
	full = ft_new_full(full);
	return (line);
}
