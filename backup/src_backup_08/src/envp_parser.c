/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:41:08 by mmago             #+#    #+#             */
/*   Updated: 2022/08/11 20:42:21 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ** ENVP маллочим и перезаписываем ** //

char	**malloc_envp(char **envp)
{
	char	**envp_1;
	int		i;
	int		o;

	i = -1;
	o = -1;
	while (envp[++i]);
	envp_1 = malloc(sizeof(char *) * (i + 1));
	envp_1[i + 1] = NULL;
	i = -1;
	while (envp[++i])
	{
		while (envp[i][++o]);
		envp_1[i] = malloc(sizeof(char) * (o + 1));
		envp_1[i][o + 1] = '\0';
		o = 0;
		while (envp[i][o])
		{
			envp_1[i][o] = envp[i][o];
			o++;
		}
		o = -1;
	}
	return (envp_1);
}

// ** ENVP перезаписываем путь после CD ** //

char	**find_pwd(t_data *data)
{
	char	*new_pwd;
	char	**old_pwd;
	int		i;

	i = 0;
	while (data->envp[i] && ft_strnstr(data->envp[i], "PWD", 3) == 0)
		i++;
	if (!data->envp[i])
		return (data->envp);
	old_pwd = ft_split(data->envp[i], '=');
	if (data->envp[i])
		free(data->envp[i]);
	if (data->envp[i + 1])
		free(data->envp[i + 1]);
	new_pwd = malloc((sizeof(char) * 200));
	getcwd(new_pwd, 150);
	data->envp[i] = ft_strjoin("PWD=", new_pwd);
	data->envp[i + 1] = ft_strjoin("OLDPWD=", old_pwd[1]);
	i = 0;
	free(new_pwd);
	free_str(old_pwd);
	return (data->envp);
}
