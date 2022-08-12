/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:48:00 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:51 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_printf(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putstr_printf("-2147483648");
		return (len);
	}
	if (n < 0)
	{
		len += ft_putchar_printf('-');
		n *= -1;
	}
	if (n >= 10)
	{
		len += ft_putnbr_printf(n / 10);
	}
	len += ft_putchar_printf(n % 10 + '0');
	return (len);
}
