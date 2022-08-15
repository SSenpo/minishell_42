/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:38:21 by mmago             #+#    #+#             */
/*   Updated: 2022/08/15 19:54:49 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/global.h"

// ** Мейник, считываем с помощью редлайна строку в нашей оболочке ** //

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		free(data);
		ft_putstr_fd("Error: malloc\n", 2);
		return (-1);
	}
	ft_data_null(data);
	if (ac != 0 && !(*av))
	{
		free(data);
		ft_putstr_fd("Error: wrong number of argument's\n", 2);
		return (-1);
	}
	ft_start_shell(data, envp);
	free(data);
	return (data->status);
}

void	ft_start_shell(t_data *data, char **envp)
{
	g_status = &data->status;
	data->status = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	data->pid_main = fork();
	if (data->pid_main == 0)
	{
		data->envp = malloc_envp(envp);
		signal(SIGINT, handler_two);
		signal(SIGQUIT, SIG_IGN);
		ft_loop_shell(data->get_string, data);
		rl_clear_history();
		free_str(data->envp);
		exit (1);
	}
	waitpid(data->pid_main, &data->status, 0);
	data->status = ft_change_status(data->status);
}

void	ft_loop_shell(char *str, t_data *data)
{
	while (1)
	{
		ft_data_null(data);
		str = readline("shell-1.0$ ");
		add_history(str);
		str = ft_string(str, data);
		str = ft_do_minishell(str, data);
		if (str)
			free(str);
	}
}

char	*ft_do_minishell(char *str, t_data *data)
{
	if (data->pipe_flag < 1)
	{
		if (get_str(str) == 0)
		{
			data->pid_child = fork();
			if (data->pid_child == 0)
				check_str(str, data);
			else
			{
				waitpid(data->pid_child, &data->status, 0);
				data->status = ft_change_status(data->status);
			}
		}
		else if (get_str(str) > 0)
		{
			ft_check_str_for_direct(str, data);
			data->envp = built_cmd(str, get_str(str), data);
			data->status = 0;
		}
	}
	else
		ft_make_a_pipe(str, data);
	return (str);
}
