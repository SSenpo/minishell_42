/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:52:02 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:47 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_help(char c, va_list list)
{
	int	i;

	i = 0;
	if (c == 'd' || c == 'i')
		i += (ft_putnbr_printf(va_arg(list, int)));
	else if (c == 's')
		i += (ft_putstr_printf(va_arg(list, char *)));
	else if (c == 'c')
		i += (ft_putchar_printf(va_arg(list, int)));
	else if (c == 'x')
		i += (ft_tohex(va_arg(list, unsigned int), "0123456789abcdef", 16));
	else if (c == 'X')
		i += (ft_tohex(va_arg(list, unsigned int), "0123456789ABCDEF", 16));
	else if (c == 'u')
		i += (ft_putnbr_u(va_arg(list, unsigned int)));
	else if (c == 'p')
		i += (ft_putpointer_fd(va_arg(list, unsigned long)));
	else if (c == '%')
		i += (ft_putchar_printf('%'));
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		i;
	int		l;

	if (!str)
		return (0);
	l = 0;
	i = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				break ;
			l += ft_help(str[i + 1], list);
			i++;
		}
		else
			l += ft_putchar_printf(str[i]);
		i++;
	}
	va_end(list);
	return (l);
}
