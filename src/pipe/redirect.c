#include "../../includes/minishell.h"

char	*make_redirect(char *command_str, t_data *data)
{
	int	index;

	index = -1;
	while (command_str[++index])
	{
		if (command_str[index] == 60)
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
	}
	return(command_str);
}

char	*change_fd_out(char *command_str, t_data *data, int index)
{
	int count;
	int	start;
	int	file;

	start = index + 1;
	count = 0;
	if (command_str[start] == 60)
	{
		ft_putstr_fd("shell : syntax error near unexpected token `<'\n", 2);
		exit(130);
	}
	while ((command_str[++index]) && (command_str[index] != ' '))
		count++;
	data->redir_out_str = malloc(sizeof(char) * count);
	if (!data->redir_out_str)
	{
		ft_putstr_fd("Error malloc in change_fd_out function!\n", 2);
		exit(130);
	}
	count = 0;
	while ((command_str[start]) && (command_str[start] != ' '))
	{	
		data->redir_out_str[count++] = command_str[start];
		command_str[start++] = ' ';
	}
	// data->redir_out_str[count] = '\0';
	ft_putstr_fd(data->redir_out_str, 2);
	ft_putstr_fd("\n", 2);
	file = open(data->redir_out_str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(data->redir_out_str);
	dup2(file, 1);
	ft_putstr_fd(command_str, 2);
	ft_putstr_fd("\n", 2);
	return(command_str);
	// ft_close_pipe(data);
}

char	*change_fd_in(char *command_str, t_data *data, int index)
{
	int count;
	int	start;
	int	file;

	start = index + 1;
	count = 0;
	while ((command_str[++index]) && (command_str[index] != ' '))
		count++;
	data->redir_in_str = malloc(sizeof(char) * count);
	if (!data->redir_in_str)
	{
		ft_putstr_fd("Error malloc in change_fd_out function!\n", 2);
		exit(130);
	}
	count = 0;
	while ((command_str[start]) && (command_str[start] != ' '))
	{
		ft_putstr_fd(data->redir_in_str, 2);
		ft_putstr_fd("\n", 2);
		data->redir_in_str[count] = command_str[start];
		command_str[start] = ' ';
		count++;
		start++;
	}
	data->redir_in_str[count] = '\0';
	file = open(data->redir_in_str, O_RDONLY, 0644);
	ft_putstr_fd(data->redir_in_str, 2);
	ft_putstr_fd("\n", 2);
	free(data->redir_in_str);
	if (file == -1)
		error();
	dup2(file, 0);
	ft_putstr_fd(command_str, 2);
	ft_putstr_fd("\n", 2);
	return(command_str);
	// ft_close_pipe(data);
}