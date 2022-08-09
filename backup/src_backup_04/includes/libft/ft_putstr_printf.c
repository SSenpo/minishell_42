/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:53:40 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:54 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_printf(char *s)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (s == NULL)
	{
		ft_putstr_printf("(null)");
		return (6);
	}
	while (s[i])
	{
		len += ft_putchar_printf(s[i]);
		i++;
	}
	return (len);
}
