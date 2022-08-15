/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:41:14 by mmago             #+#    #+#             */
/*   Updated: 2022/08/11 20:32:34 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ** Export - добавляем что-то в ENVP ** //

char    **exec_export(char *str, t_data *data)
{
    char	**new_str;
    int		i;

    i = -1;
	new_str = ft_split(str, ' ');
	new_str = check_split_simb(new_str);
	if ((new_str[1] && (ft_strnstr(new_str[1], "-p\0", 3) != 0)) ||
		!new_str[1])
	{
		while (data->envp[++i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(data->envp[i], 6);
		}
	}
	else
	{
		if ((new_str[1][0] > 64 && new_str[1][0] < 91) || (new_str[1][0] == 95) ||
			(new_str[1][0] > 96 && new_str[1][0] < 123))
		{
			i = 0;
    		while (data->envp[i] &&
				ft_strnstr(data->envp[i], new_str[1], ft_strlen(new_str[1])) == 0)
				i++;
			if (!data->envp[i])
				data->envp = get_export(new_str[1], data, i);
		}
	}
	free_str(new_str);
	return (data->envp);
}

char	**get_export(char *str, t_data *data, int i)
{
	char	**new_envp;
	int		s;
	int		check_str;

	s = -1;
	check_str = 0;
	while (str[++s])
	{
		if (str[s] == '=')
			check_str = 1;
	}
	if (check_str > 0)
	{
		s = -1;
		new_envp = malloc(sizeof(char *) * (i));
		if (!new_envp)
			return (data->envp);
		while (data->envp[++s])
			new_envp[s] = ft_strdup(data->envp[s]);
		new_envp[s] = ft_strdup(str);
		new_envp[s + 1] = NULL;
		free_str(data->envp);
		return (new_envp);
	}
	return (data->envp);
}

// ** PRINT ENV ** //

void	b_env(t_data *data)
{
	int	i;

	i = -1;
	while(data->envp[++i])
		ft_putstr_fd(data->envp[i], 6);
}