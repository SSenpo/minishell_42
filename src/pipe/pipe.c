/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:40:56 by mmago             #+#    #+#             */
/*   Updated: 2022/08/15 20:49:34 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_pipe(t_data *data)
{
	int	count;
	int	i;

	i = -1;
	count = -1;
	while (++count < data->pipe_flag)
	{
		while (++i < 2)
			close(data->fd_pipe[count][i]);
		free(data->fd_pipe[count]);
		i = -1;
	}
	free(data->fd_pipe);
}

void	ft_procces_build_in(t_data *data)
{
	if (data->i == 0)
		dup2(data->fd_pipe[0][1], 1);
	else if (data->i == data->pipe_flag)
		dup2(data->fd_pipe[data->i - 1][0], 0);
	else
	{
		dup2(data->fd_pipe[data->i - 1][0], 0);
		dup2(data->fd_pipe[data->i][1], 1);
	}
	if (data->redir_in_flag > 0 || data->redir_out_flag > 0)
			data->pipe_part_split[data->i] = make_redirect(
				data->pipe_part_split[data->i], data);
	data->envp = built_cmd(data->pipe_part_split[data->i],
			get_str(data->pipe_part_split[data->i]), data);
	exit(0);
}

void	ft_procces(t_data *data)
{
	if (data->i == data->if_pipe_and_heredoc_i)
	{
		if (data->pipe_part_split[data->i + 1])
			dup2(data->fd_pipe[data->i][1], 1);
		data->file_redir_fd = open("estrong_super_heredoc", O_RDONLY, 0644);
		dup2(data->file_redir_fd, 0);
		close(data->file_redir_fd);
		ft_close_pipe(data);
	}
	else if (data->i == 0)
	{
		dup2(data->fd_pipe[0][1], 1);
		ft_close_pipe(data);
	}
	else if (data->i == data->pipe_flag)
	{
		dup2(data->fd_pipe[data->i - 1][0], 0);
		ft_close_pipe(data);
	}
	else
	{
		dup2(data->fd_pipe[data->i - 1][0], 0);
		dup2(data->fd_pipe[data->i][1], 1);
		ft_close_pipe(data);
	}
	if (data->redir_in_flag > 0 || data->redir_out_flag > 0)
		data->pipe_part_split[data->i] = make_redirect(
				data->pipe_part_split[data->i], data);
	check_str(data->pipe_part_split[data->i], data);
}

void	ft_make_a_pipe(char *str, t_data *data)
{
	int	count;

	count = -1;
	data->i = -1;
	data->num_pipe = 0;
	data->pipe_part_split = ft_split(str, '|');
	data->fd_pipe = malloc(sizeof(int *) * data->pipe_flag);
	while (++count < data->pipe_flag)
	{
		data->fd_pipe[count] = malloc(sizeof(int) * 2);
		pipe(data->fd_pipe[count]);
	}
	while (data->pipe_part_split[++data->i])
	{
		ft_check_str_for_direct(data->pipe_part_split[data->i],
			data);
		if (data->heredoc_flag > 0)
		{
			data->if_pipe_and_heredoc_i = data->i;
			data->pipe_part_split[data->i] = make_redirect(
					data->pipe_part_split[data->i], data);
			dup2(data->std_out_fd, 1);
			dup2(data->std_in_fd, 0);
		}
		ft_redirect_null(data);
	}
	data->i = -1;
	while (data->pipe_part_split[++data->i])
	{
		ft_check_str_for_direct(data->pipe_part_split[data->i],
			data);
		data->pipe_fork = fork();
		if (data->pipe_fork == 0)
		{
			if (get_str(data->pipe_part_split[data->i]) > 0)
				ft_procces_build_in(data);
			ft_procces(data);
		}
		ft_redirect_null(data);
	}
	ft_close_pipe(data);
	while (data->stop_procces < data->i)
	{
		waitpid(-1, &data->status, 0);
		data->status = ft_change_status(data->status);
		data->stop_procces++;
	}
	free_str(data->pipe_part_split);
	return ;
}

void	ft_check_str_for_pipe(char *str, t_data *data)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 124)
			data->pipe_flag++;
	}
}

void	ft_check_str_for_direct(char *str, t_data *data)
{
	int		i;
	char	c;

	i = -1;
	c = 60;
	while (str[++i])
	{
		if (str[i] == c || str[i] == (c + 2))
		{
			if (str[i + 1] && str[i] == c && str[i + 1] != c)
				data->redir_in_flag++;
			else if (str[i + 1] && str[i] == c && str[i + 1] == c)
				data->heredoc_flag++;
			else if (str[i + 1] && str[i] == c + 2 &&
				str[i + 1] != c + 2)
				data->redir_out_flag++;
		}
	}
}

void	ft_redirect_null(t_data *data)
{
	data->redir_in_flag = 0;
	data->redir_out_flag = 0;
	data->heredoc_flag = 0;
}

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
	return (NULL);
}

void	check_str(char *str, t_data *data)
{
	char	**command;
	char	*path;

	ft_check_str_for_direct(str, data);
	if (data->redir_in_flag > 0 || data->redir_out_flag > 0
		|| data->heredoc_flag > 0)
		str = make_redirect(str, data);
	command = ft_split(str, ' ');
	command = check_split_simb(command);
	path = find_path(command[0], data);
	if (!path)
	{
		if (command[0][0] == '|' || command[0][0] == '!' || command[0][0] == '&' ||
			command[0][0] == '%' || command[0][0] == ')' || command[0][0] == '^' ||
			command[0][0] == ';')
		{
			if (command[0][0] == '^')
				ft_putstr_fd("shell : :s^: no previous substitution\n", 2);
			else if (command[0][0] == '%')
				ft_putstr_fd("shell : fg: %%: no such job\n", 2);
			else if (command[0][0] == '!')
				ft_putstr_fd("shell : syntax error near unexpected token 'newline'\n", 2);
			else
			{
				ft_putstr_fd("shell : syntax error near unexpected token '", 2);
				ft_putstr_fd(command[0], 2);
				ft_putstr_fd("'\n", 2);
			}
		}
		else
		{
			if (ft_strncmp(command[0], "./minishell\0", 14) == 0)
			{
				free(path);
				path = ft_strdup("/Users/mmago/minishell_mmago/shell/minishell");
				if (execve(path, command, data->envp) == -1)
					error();
			}
			ft_putstr_fd("shell : ", 2); 
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(" : command not found\n", 2);
		}
		exit(127);
	}
	if (execve(path, command, data->envp) == -1)
		error();
}
