#include "../../includes/minishell.h"

char	*make_redirect(char *command_str, t_data *data)
{
	int	index;

	index = -1;
	while (command_str[++index])
	{
		if (command_str[index + 1] && command_str[index] == 60 &&
			command_str[index + 1] != 60)
		{
			if (!command_str[index + 1])
			{
				ft_putstr_fd("shell : syntax error near unexpected token `newline'\n", 2);
				exit(130);
			}
			command_str = change_fd_in(command_str, data, index);
		}
		else if (command_str[index] == 62)
		{
			if (!command_str[index + 1])
			{
				ft_putstr_fd("shell : syntax error near unexpected token `newline'\n", 2);
				exit(130);
			}
			command_str = change_fd_out(command_str, data, index);
		}
		else if (command_str[index + 1] && command_str[index] == 60 &&
			command_str[index + 1] == 60)
		{
			// ft_putnbr_fd(data->heredoc_flag, 2);
			// ft_putstr_fd("\n", 2);
			command_str = change_heredoc(command_str, data, index);
		}
	}
	return(command_str);
}

char	*change_fd_out(char *command_str, t_data *data, int index)
{
	int file_name_len;
	int	file_name_start;
	int	start;

	start = index + 1;
	command_str[index] = ' ';
	file_name_len = 0;
	file_name_start = 0;
	if (command_str[start] == 60)
	{
		ft_putstr_fd("shell : syntax error near unexpected token `<'\n", 2);
		exit(130);
	}
	while (command_str[start])
	{
		if (command_str[start] == ' ')
			start++;
		else
		{
			file_name_start = start;
			while (command_str[start] && command_str[start] != ' ')
			{
				file_name_len++;
				start++;
			}
			break;
		}
	}
	data->redir_out_str = malloc(sizeof(char) * (file_name_len + 1));
	if (!data->redir_out_str)
	{
		ft_putstr_fd("Error malloc in change_fd_out function!\n", 2);
		exit(130);
	}
	index = 0;
	while (file_name_len > 0)
	{
		data->redir_out_str[index++] = command_str[file_name_start++];
		command_str[file_name_start - 1] = ' ';
		file_name_len--;
	}
	data->redir_out_str[index] = '\0';
	data->file_redir_fd = open(data->redir_out_str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(data->redir_out_str);
	dup2(data->file_redir_fd, 1);
	return(command_str);
}

char	*change_fd_in(char *command_str, t_data *data, int index)
{
	int file_name_len;
	int	file_name_start;
	int	start;
	int	i = 0;

	start = index + 1;
	command_str[index] = ' ';
	file_name_len = 0;
	file_name_start = 0;
	if (command_str[start] == 62)
	{
		ft_putstr_fd("shell : syntax error near unexpected token `>'\n", 2);
		exit(130);
	}
	if (command_str[start] == command_str[index])
	{
		while (command_str[start + 1] && command_str[start + 1] == ' ')
			start++;
		if (!command_str[start + 1])
			exit(130);
		while (command_str[start + 1] && command_str[start] != ' ')
		{
			data->delimiter[i] = command_str[start + 1];
			command_str[start + 1] = ' ';
			start++;
			i++;
		}
		ft_do_heredoc(data);
	}
	while (command_str[start])
	{
		if (command_str[start] == ' ')
			start++;
		else
		{
			file_name_start = start;
			while (command_str[start] && command_str[start] != ' ')
			{
				file_name_len++;
				start++;
			}
			break;
		}
	}
	data->redir_in_str = malloc(sizeof(char) * (file_name_len + 1));
	if (!data->redir_in_str)
	{
		ft_putstr_fd("Error malloc in change_fd_out function!\n", 2);
		exit(130);
	}
	index = 0;
	while (file_name_len > 0)
	{
		data->redir_in_str[index++] = command_str[file_name_start++];
		command_str[file_name_start - 1] = ' ';
		file_name_len--;
	}
	data->redir_in_str[index] = '\0';
	data->file_redir_fd = open(data->redir_in_str, O_RDONLY, 0644);
	if (data->file_redir_fd == -1)
		error();
	dup2(data->file_redir_fd, 0);
	free(data->redir_in_str);
	return(command_str);
}

char	*change_heredoc(char *command_str, t_data *data, int index)
{
	int	start;
	int	old_start;
	int	len;
	int	i = 0;

	len = 0;
	start = index + 2;
	command_str[index] = ' ';
	command_str[index + 1] = ' ';
	while (command_str[start] && command_str[start] == ' ')
		start++;
	if (!command_str[start])
		exit(130);
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
	return(command_str);
}