/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:38:21 by mmago             #+#    #+#             */
/*   Updated: 2022/07/09 22:25:32 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_data_null(t_data * data)
{
	data->flag_path = 0;
	data->pid_main = 0;
	data->flag = 0;
	data->get_pipe = 0;
	data->check_pipe_flag = 0;
	data->pipe_flag = 0;
	data->pipe_fork = 0;
	data->num_pipe = 0;
	data->i = 0;
	data->stop_procces = 0;
}

// ** Мейник, считываем с помощью редлайна строку в нашей оболочке ** //

static int		*g_status;

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	// char	*str;

	// str = NULL;
	data = malloc(sizeof(t_data));
	ft_data_null(data);
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
	g_status = &data->status;
	data->status = 1;
	data->get_string = NULL;
	signal(SIGINT, SIG_IGN);
	if (1)
	{
		data->pid_main = fork();
		if (data->pid_main == 0)
			ft_loop_shell(data->get_string, envp, data);
		waitpid(data->pid_main, &data->status, 0);
		data->status = ft_change_status(data->status);
		printf("STATUS = %d\n", data->status);
	}
	free(data);
	// system("leaks minishell");
	exit(data->status);
}

void	ft_loop_shell(char *str, char **envp, t_data *data)
{
	int					pid;

	data->envp = malloc_envp(envp);
	signal(SIGINT, handler_two);
	while (1)
	{
		ft_data_null(data);
		str = readline("shell-1.0$ ");
		add_history(str);
		str = ft_string(str, data);
		ft_check_str_for_pipe(str, data);
		if (get_str(str) == 0 && data->pipe_flag < 1)
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
		else if(get_str(str) != -1 && data->pipe_flag < 1)
		{
			data->envp = built_cmd(str, get_str(str), data);
			data->status = 0;
		}
		else
			ft_make_a_pipe(str, data);
		if (str)
			free(str);
	}
	rl_clear_history();
	free_str(data->envp);
	exit (77);
}

// void	handler(int signum)
// {
// 	if (signum == SIGINT)
// 		*g_status = 1;
// }

void	handler_two(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_redisplay();
		*g_status = 1;
	}
}