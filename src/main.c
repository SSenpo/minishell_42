#include "../includes/minishell.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

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

int	main(int ac, char **av, char **envp)
{
	char *str;
	int	pid;

	str = NULL;
	if (ac != 0 && !(*av))
		return (0);
	while (1)
	{
		str = readline("$");
		pid = fork();
		if (pid == 0)
			check_str(str, envp);
		else
			waitpid(pid, NULL, 0);
		// printf("COPY = %s\n", str);
		free(str);
	}
	return (0);
}