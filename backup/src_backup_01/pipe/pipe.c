#include "../../includes/minishell.h"

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

// ** Тут выполнение команды Shell ** //

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

	command = ft_split(str, ' ');
	path = find_path(command[0], envp);
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
	if (execve(path, command, envp) == -1)
		error();
}
