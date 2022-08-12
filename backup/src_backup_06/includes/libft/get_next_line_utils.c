/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:47:17 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:08:07 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_gnl(char *full)
{
	char	*str;
	int		i;

	i = 0;
	if (!full[i])
		return (NULL);
	while (full[i] && full[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (full[i] && full[i] != '\n')
	{
		str[i] = full[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_full(char *full)
{
	int		i;
	int		o;
	char	*str;

	i = 0;
	while (full[i] && full[i] != '\n')
		i++;
	if (!full[i])
	{
		free(full);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen_gnl(full) - i + 1));
	if (!str)
		return (NULL);
	i++;
	o = 0;
	while (full[i])
		str[o++] = full[i++];
	str[o] = '\0';
	free(full);
	return (str);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen_gnl(s)]);
	while (s[i])
	{
		if (s[i] == (char )c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *full, char *buff)
{
	char	*str;
	size_t	i;
	size_t	o;

	if (!full)
	{
		full = malloc(sizeof(char) * 1);
		full[0] = '\0';
	}
	if (!full || !buff)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_strlen_gnl(full) + ft_strlen_gnl(buff)
				+ 1));
	if (!str)
		return (NULL);
	i = -1;
	o = 0;
	if (full)
		while (full[++i] != '\0')
			str[i] = full[i];
	while (buff[o] != '\0')
		str[i++] = buff[o++];
	str[ft_strlen_gnl(full) + ft_strlen_gnl(buff)] = '\0';
	free(full);
	return (str);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
