/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:06:09 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:59 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	size_t	dsti;
	size_t	srci;
	size_t	i;

	dsti = ft_strlen(dst);
	srci = ft_strlen(src);
	i = 0;
	if (dstsize <= dsti)
		return (srci + dstsize);
	while (src[i] && i < (dstsize - dsti - 1))
	{
		dst[dsti + i] = src[i];
		i++;
	}
	dst[dsti + i] = '\0';
	srci += dsti;
	return (srci);
}
