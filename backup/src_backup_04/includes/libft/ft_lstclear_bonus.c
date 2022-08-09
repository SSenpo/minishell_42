/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:09:09 by mmago             #+#    #+#             */
/*   Updated: 2022/04/11 21:07:40 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*check;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		check = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = check;
	}
}
