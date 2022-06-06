#include "../includes/minishell.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

// ** Тут мой пайпикс, а точнее, выполнение любой команды оболочки Shell ** //

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
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	check_str(char *str, char **envp)
{
	char	**command;
	char	*path;
	int		i;

	i = 0;
	command = ft_split(str, ' ');
	
	path = find_path(command[0], envp);
	if (!path)
	{
		while (command[i++])
			free(command[i]);
		free(command);
		write(2, "Error: Wrong command\n", 22);
		exit(127);
	}
	if (execve(path, command, envp) == -1)
		error();
}
// ** ------------------------------------------------------------ ** //

// ** Мейник, считываем с помощью редлайна строку в нашей оболочке ** //

int	main(int ac, char **av, char **envp)
{
	char *str;
	int	pid;

	str = NULL;
	if (ac != 0 && !(*av))
		return (0);
	while (1)
	{
		str = readline("miniShell $");
		if (get_str(str) == 0)
		{
			pid = fork();
			if (pid == 0)
				check_str(str, envp);
			else
				waitpid(pid, NULL, 0);
		}
		else
		{
			cd(str);
			envp = find_pwd(envp);
		}
		free(str);
	}
	return (0);
}