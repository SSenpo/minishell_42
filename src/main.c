/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:38:21 by mmago             #+#    #+#             */
/*   Updated: 2022/06/16 01:24:54 by mmago            ###   ########.fr       */
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

	i = 0;
	command = ft_split(str, ' ');
	path = find_path(command[0], envp);
	if (!path)
	{
		printf("zsh: command not found: %s\n", command[0]);
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
	char *str;
	// int	ppid;
	int	pid;

	str = NULL;
	if (ac != 0 && !(*av))
		return (0);
	// ppid = fork();
	envp = malloc_envp(envp);
	while (1)
	{
		str = readline("miniShell $");
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
		if (get_str(str) != -1 && get_str(str) != 0)
			envp = built_cmd(str, get_str(str), envp);
		if (str)
			free(str);
		// system("leaks minishell");
	}
	rl_clear_history();
	free_str(envp);
	return (0);
}