/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:41:12 by mmago             #+#    #+#             */
/*   Updated: 2022/07/04 15:12:28 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ** Выполнение функции EXIT ** //

int	ft_exit_print(char *str)
{
	char	**s;
	int		status_exit;

	status_exit = 0;
	s = ft_split(str, ' ');
	if (s[1])
		status_exit = ft_atoi(s[1]);
	exit(status_exit);
}

int	ft_change_status(int status)
{
	if (status > 0)
		status /= 256;
	return (status);
}

void	free_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}