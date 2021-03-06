/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:41:12 by mmago             #+#    #+#             */
/*   Updated: 2022/07/17 21:04:06 by mmago            ###   ########.fr       */
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
	s = check_split_simb(s);
	if (s[1])
	{
		if (check_num_or_not(s[1]) != -777)
			status_exit = ft_atoi(s[1]);
		else
		{
			status_exit = 255;
			printf("shell : exit: %s: numeric argument required\n", s[1]);
		}
	}
	exit(status_exit);
}

int	check_num_or_not(const char *str)
{
	int			i;
	long long	num;
	int			minus;

	i = 0;
	num = 0;
	minus = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	if (str[i] <= '0' || str[i] >= '9')
		return (-777);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	return (num * minus);
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