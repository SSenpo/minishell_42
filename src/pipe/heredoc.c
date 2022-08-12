#include "../../includes/minishell.h"

void	ft_do_heredoc(t_data *data)
{
	char *readline_str;
	int	heredoc_file;
	int	heredoc_pid;

	heredoc_file = open("estrong_super_heredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	heredoc_pid = fork();
	if (heredoc_pid == 0)
	{
		while (1)
		{
			readline_str = readline("> ");
			if (ft_strncmp(readline_str, data->delimiter,
				ft_strlen(data->delimiter)) == 0)
				break;
			ft_putstr_fd(readline_str, heredoc_file);
			ft_putstr_fd("\n", heredoc_file);
			free(readline_str);
		}
		close(heredoc_file);
		exit(0);
	}
	else
	{
		waitpid(heredoc_pid, &data->status, 0);
		close(heredoc_file);
		if (data->delimiter)
			free(data->delimiter);
		heredoc_file = open("estrong_super_heredoc", O_RDONLY, 0644);
		dup2(heredoc_file, 0);
		close(heredoc_file);
		return ;
	}
}