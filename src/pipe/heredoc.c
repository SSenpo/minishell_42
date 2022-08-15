/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:41:03 by mmago             #+#    #+#             */
/*   Updated: 2022/08/15 20:42:08 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_do_heredoc(t_data *data)
{
	char	*readline_str;
	int		heredoc_file;
	int		heredoc_pid;

	heredoc_file = open("estrong_super_heredoc",
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	heredoc_pid = fork();
	if (heredoc_pid == 0)
	{
		while (1)
		{
			readline_str = readline("> ");
			if (ft_strncmp(readline_str, data->delimiter,
					ft_strlen(data->delimiter)) == 0)
				break ;
			ft_putstr_fd(readline_str, heredoc_file);
			ft_putstr_fd("\n", heredoc_file);
			free(readline_str);
		}
		close(heredoc_file);
		exit(0);
	}
	else
	{
		waitpid(-1, &data->status, 0);
		close(heredoc_file);
		if (data->delimiter)
			free(data->delimiter);
		heredoc_file = open("estrong_super_heredoc", O_RDONLY, 0644);
		dup2(heredoc_file, 0);
		close(heredoc_file);
		return ;
	}
}

char	*change_heredoc(char *command_str, t_data *data, int index)
{
	int	start;
	int	old_start;
	int	len;
	int	i;

	i = 0;
	len = 0;
	start = index + 2;
	command_str[index] = ' ';
	command_str[index + 1] = ' ';
	while (command_str[start] && command_str[start] == ' ')
		start++;
	if (!command_str[start])
		return (command_str);
	old_start = start;
	while (command_str[start] && command_str[start] != ' ')
	{
		start++;
		len++;
	}
	data->delimiter = malloc(sizeof(char) * (len + 1));
	while (command_str[old_start] && command_str[old_start] != ' ')
	{
		data->delimiter[i] = command_str[old_start];
		command_str[old_start] = ' ';
		old_start++;
		i++;
	}
	ft_do_heredoc(data);
	return (command_str);
}
