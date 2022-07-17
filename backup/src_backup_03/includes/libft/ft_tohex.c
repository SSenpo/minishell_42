/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:00:34 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:08:06 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tohex(unsigned long int nb, char *to, int base)
{
	int	len;

	len = 0;
	if (nb >= (unsigned long int)base)
		len += ft_tohex(nb / base, to, base);
	len += ft_putchar_printf(to[nb % base]);
	return (len);
}
