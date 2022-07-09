/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:40:56 by mmago             #+#    #+#             */
/*   Updated: 2022/07/05 21:48:04 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_make_a_pipe(char *str, t_data *data);
// {

// }

// void	ft_check_str_for_pipe(char *str, t_data *data)
// {
// 	int	i;
	
// 	i = -1;
// 	while(str[++i])
// 	{
// 		if (str[i] == 124)
// 			data->pipe_flag++;
// 	}
// }

// ** Тут выполнение команды Shell ** //

char	*find_path(char *command, t_data *data)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(data->envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(data->envp[i] + 5, ':');
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

void	check_str(char *str, t_data *data)
{
	char	**command;
	char	*path;

	command = ft_split(str, ' ');
	path = find_path(command[0], data);
	if (!path)
	{
		if (command[0][0] == '|' || command[0][0] == '!' || command[0][0] == '&' ||
			command[0][0] == '%' || command[0][0] == ')' || command[0][0] == '^' ||
			command[0][0] == ';')
		{
			if (command[0][0] == '^')
				printf("shell : :s^: no previous substitution\n");
			else if (command[0][0] == '%')
				printf("shell : fg: %%: no such job\n");
			else if (command[0][0] == '!')
				printf("shell : syntax error near unexpected token 'newline'\n");
			else
				printf("shell : syntax error near unexpected token '%s'\n", command[0]);
		}
		else
			printf("shell : %s: command not found\n", command[0]);
		free_str(command);
		exit(127);
	}
	if (execve(path, command, data->envp) == -1)
		error();
}
