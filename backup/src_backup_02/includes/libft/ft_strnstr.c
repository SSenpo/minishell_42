/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:31:48 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:08:03 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len1;

	if (*needle == '\0')
		return ((char *)haystack);
	len1 = ft_strlen(needle);
	while (*haystack != '\0' && len-- >= len1)
	{
		if (*haystack == *needle
			&& ft_memcmp(haystack, needle, len1) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
