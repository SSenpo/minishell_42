/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:38:21 by mmago             #+#    #+#             */
/*   Updated: 2022/07/04 19:26:46 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	data->status = 1;
	while (data->status != 0)
	{
		data->pid_main = fork();
		if (data->pid_main == 0)
			ft_loop_shell(str, envp, data);
		waitpid(data->pid_main, &data->status, 0);
		data->status = ft_change_status(data->status);
		printf("STATUS = %d\n", data->status);
	}
	free(data);
	system("leaks minishell");
	exit(data->status);
}

void	ft_loop_shell(char *str, char **envp, t_data *data)
{
	int					pid;
	data->envp = malloc_envp(envp);
	while (1)
	{
		str = readline("shell-1.0$ ");
		add_history(str);
		str = ft_string(str, data);
		if (get_str(str) == 0)
		{
			pid = fork();
			if (pid == 0)
				check_str(str, data);
			else
			{
				waitpid(pid, &data->status, 0);
				data->status = ft_change_status(data->status);
			}
		}
		else if(get_str(str) != -1)
		{
			data->envp = built_cmd(str, get_str(str), data);
			data->status = 0;
		}
		if (str)
			free(str);
	}
	rl_clear_history();
	free_str(data->envp);
	exit (77);
}
