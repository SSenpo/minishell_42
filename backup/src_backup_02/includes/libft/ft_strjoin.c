/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:28:36 by mmago             #+#    #+#             */
/*   Updated: 2022/06/21 14:45:17 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int	i;
	int	o;

	if (!s1 && !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	i = -1;
	o = -1;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++o])
	{
		s3[i] = s2[o];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}