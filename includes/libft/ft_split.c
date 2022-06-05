/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:18:12 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:55 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_partlen(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static int	ft_countpart(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char	**ft_free(int i, char *str)
{
	while (i > 0)
		free(&str[i--]);
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	int			j;
	int			countlen;
	char		**str;

	i = 0;
	if (!s)
		return (NULL);
	countlen = ft_countpart(s, c);
	str = (char **)malloc(sizeof(char *) * (countlen + 1));
	if (!str)
		return (NULL);
	str[countlen] = NULL;
	i = -1;
	j = 0;
	while (++i < countlen)
	{
		while (s[j] == c)
			j++;
		str[i] = ft_substr(s, j, ft_partlen(&s[j], c));
		if (!str[i])
			return (ft_free(i, str[i]));
		j = j + ft_partlen(str[i], c);
	}
	return (str);
}
