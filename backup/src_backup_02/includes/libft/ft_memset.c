/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:10:30 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:46 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*mas;
	unsigned char	sum;

	mas = (unsigned char *)b;
	sum = (unsigned char) c;
	while (len--)
		*mas++ = sum;
	return (b);
}
