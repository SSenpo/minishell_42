/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:38:21 by mmago             #+#    #+#             */
/*   Updated: 2022/06/17 17:11:41 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// ** Тут мой пайпикс, а точнее, выполнение любой команды оболочки Shell ** //

char	*find_path(char *command, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, command);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_str(paths);
			return (path);
		}
		free(path);
		i++;
	}
	i = -1;
	free_str(paths);
	return (0);
}

void	check_str(char *str, char **envp)
{
	char	**command;
	char	*path;
	int		i;
	// int		flag;

	i = -1;
	// flag = 0;
	command = ft_split(str, ' ');
	// while (command[++i])
	// {
	// 	if (command[i][0] == '|')
	// 		flag = 2;
	// }
	path = find_path(command[0], envp);
	if (!path)
	{
		if (command[0][0] == '|' || command[0][0] == '!' || command[0][0] == '&')
			printf("shell : syntax error near unexpected token '%s'\n", command[0]);
		else
			printf("shell : command not found: %s\n", command[0]);
		free_str(command);
		exit(127);
	}
	if (execve(path, command, envp) == -1)
		error();
}
// ** ------------------------------------------------------------ ** //

// ** Мейник, считываем с помощью редлайна строку в нашей оболочке ** //

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*str;

	str = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		free(data);
		write(1, "Error: malloc\n", 14);
		return (-1);
	}
	if (ac != 0 && !(*av))
	{
		free(data);
		write(1, "Error: wrong number of argument's\n", 34);
		return (0);
	}
	data->pid_main = fork();
	if (data->pid_main == 0)
		ft_loop_shell(str, envp, data);
	waitpid(data->pid_main, NULL, 0);
	// ft_free(envp);
	free(data);
	return (0);
}

void	ft_loop_shell(char *str, char **envp, t_data *data)
{
	int	pid;

	data->flag_path = 0;
	envp = malloc_envp(envp);
	while (1)
	{
		str = readline("shell-1.0$ ");
		add_history(str);
		str = ft_string(str);
		if (get_str(str) == 0)
		{
			pid = fork();
			if (pid == 0)
				check_str(str, envp);
			else
				waitpid(pid, NULL, 0);
		}
		else if(get_str(str) != -1)
			envp = built_cmd(str, get_str(str), envp);
		if (str)
			free(str);
	}
	rl_clear_history();
	free_str(envp);
	exit (0);
}