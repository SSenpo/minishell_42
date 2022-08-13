/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:41:18 by mmago             #+#    #+#             */
/*   Updated: 2022/07/18 21:23:40 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ** Unset - удаляем что-то из ENVP ** //

char	**b_unset(char *str, t_data *data)
{
	int		i;
	char	**new_str;

	i = 0;
	new_str = ft_split(str, ' ');
	new_str = check_split_simb(new_str);
	if (new_str[i + 1])
	{
		while (data->envp[i] &&
			ft_strnstr(data->envp[i], new_str[1], ft_strlen(new_str[1])) == 0)
			i++;
	}
	if (new_str[1] && data->envp[i])
		data->envp = del_var(new_str[1], data);
	else
	{
		if (new_str[1])
		{
			ft_putstr_fd("shell : unset: `", 2);
			ft_putstr_fd(new_str[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
	}
	free_str(new_str);
	return (data->envp);
}

char	**del_var(char *str, t_data *data)
{
	int	i;

	i = 0;
	while(data->envp[i])
	{
		if ((ft_strnstr(data->envp[i], str, ft_strlen(str)) == 0))
			i++;
		else
			break;
	}
	while (data->envp[i + 1])
	{
		free(data->envp[i]);
		data->envp[i] = ft_strdup(data->envp[i + 1]);
		i++;
	}
	free(data->envp[i]);
	data->envp[i] = NULL;
	return (data->envp);
}