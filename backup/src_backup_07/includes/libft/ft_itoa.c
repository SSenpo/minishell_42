/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:19:15 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:38 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_result(int n, int size)
{
	long long	p;
	char		*str;

	p = n;
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (p != 0)
	{
		size--;
		str[size] = (p % 10) * ((p > 0) * 2 - 1) + '0';
		p /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long long	p;
	char		*str;
	int			size;

	p = n;
	size = 0;
	if (n == 0)
	{
		str = ft_result(n, 1);
		str[0] = '0';
		return (str);
	}
	while ((p % 10 || p / 10) && p != 0)
	{
		size++;
		p = p / 10;
	}
	size += (n < 0);
	str = ft_result(n, size);
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	return (str);
}
