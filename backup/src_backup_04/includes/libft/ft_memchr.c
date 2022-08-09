/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:19:03 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:44 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	d;

	p = (unsigned char *)s;
	d = (unsigned char)c;
	while (n--)
	{
		if (*p == d)
		{
			return (p);
		}
		p++;
	}
	return (NULL);
}
