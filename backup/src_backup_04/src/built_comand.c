/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:41:05 by mmago             #+#    #+#             */
/*   Updated: 2022/07/17 20:17:22 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ** Тут будем проверять строку на builtin команды, которые нужно выполнять отдельно ** //

int	get_str(char *str)
{
	char **pars_str;
	int	i;

	i = 0;
	if (!str[i])
		return -1;
	pars_str = ft_split(str, ' ');
	i = 0;
	if (pars_str[i])
	{
		if (ft_strncmp(pars_str[0], "cd\0", 3) == 0)
			i = 1;
		else if (ft_strncmp(pars_str[0], "pwd\0", 4) == 0)
			i = 2;
		else if (ft_strncmp(pars_str[0], "echo\0", 5) == 0)
			i = 3;
		else if (ft_strncmp(pars_str[0], "unset\0", 6) == 0)
			i = 4;
		else if (ft_strncmp(pars_str[0], "env\0", 4) == 0)
			i = 5;
		else if (ft_strncmp(pars_str[0], "export\0", 7) == 0)
			i = 6;
		else if (ft_strncmp(pars_str[0], "exit\0", 5) == 0)
			i = 7;
	}
	free_str(pars_str);
	return (i);
}

// ** Определяем билд команду ** //

char	**built_cmd(char *str, int r, t_data *data)
{
	if (r == 1)
	{
		cd(str);
		data->envp = find_pwd(data);
	}
	else if (r == 2)
		pwd_command(str);
	else if (r == 3)
		echo_command(str);
	else if (r == 4)
		data->envp = b_unset(str, data);
	else if (r == 5)
		b_env(data);
	else if (r == 6)
		data->envp = exec_export(str, data);
	else if (r == 7)
		ft_exit_print(str);
	return (data->envp);
}

// ** Выполнение функции CD ** //

int cd(char *str)
{
	char **new_str;

	new_str = ft_split(str, ' ');
	new_str = check_split_simb(new_str);
	if (new_str[1])
	{
		if (chdir(new_str[1]) != 0)
		{
			printf("cd: no such file or directory: %s\n", new_str[1]);
			free_str(new_str);
			return (1);
		}
	}
	else
		chdir("..");
	free_str(new_str);
	return (0);
}

// ** Выполнение функции PWD ** //

void	pwd_command(char *str)
{
	char *print_pwd;
	char **check;

	check = ft_split(str, ' ');
	check = check_split_simb(check);
	print_pwd = malloc(sizeof(char) * 200);
	getcwd(print_pwd, 190);
	if (check[1] && (ft_strncmp(check[1], "-", 1) == 0))
	{
		if ((ft_strncmp(check[1], "-L\0", 3) == 0) || (ft_strncmp(check[1], "-P\0", 3) == 0) ||
				(ft_strncmp(check[1], "-LP\0", 4) == 0))
			printf("%s\n", print_pwd);
		else
			printf("pwd: usage: pwd [-LP]\n");
	}
	else
		printf("%s\n", print_pwd);
	free(print_pwd);
	free_str(check);
}

// ** Выполнение функции ECHO ** //

void	echo_command(char *str)
{
	char **check;
	int		i;

	i = 0;
	check = ft_split(str, ' ');
	check = check_split_simb(check);
	if (check[1] && (ft_strncmp(check[1], "-n\0", 2) == 0))
	{
		i = 1;
		while (check[++i] && check[i + 1])
			printf("%s ", check[i]);
		if (check[i])
			printf("%s", check[i]);
	}
	else if (check[1] && (ft_strncmp(check[1], "-n\0", 2) != 0))
	{
		while (check[++i])
			printf("%s ", check[i]);
		if (check[i])
			printf("%s", check[i]);
		printf("\n");
	}
	else
		printf("\n");
	free_str(check);
}