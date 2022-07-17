/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:01:57 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:52 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putpointer_fd(unsigned long n)
{
	char	*hex;
	char	tmp[17];
	int		len;
	int		i;

	if (!n)
	{
		write(1, "0x0", 3);
		return (3);
	}
	i = 0;
	hex = "0123456789abcdef";
	while (n)
	{
		tmp[i++] = hex[n % 16];
		n /= 16;
	}
	tmp[i] = '\0';
	len = i + 2;
	i--;
	write(1, "0x", 2);
	while (i >= 0)
		write(1, &tmp[i--], 1);
	return (len);
}
