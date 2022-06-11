#include "../includes/minishell.h"

// ** Определяем билд команду ** //

char	**built_cmd(char *str, int r, char **envp)
{
	if (r == 1)
	{
		cd(str);
		envp = find_pwd(envp);
	}
	if (r == 2)
		pwd_command(str);
	if (r == 3)
		echo_command(str);
	if (r == 4)
		envp = b_unset(str, envp);
	if (r == 5)
		b_env(envp);
	return (envp);
}

// ** Выполнение функции CD ** //

int cd(char *str)
{
	char **new_str;

	new_str = ft_split(str, ' ');
	if (new_str[1])
	{
		if (chdir(new_str[1]) != 0)
		{
			printf("cd: no such file or directory: %s\n", new_str[1]);
			free_str(new_str);
			return (1);
		}
	}
	else
		chdir("..");
	free_str(new_str);
	return (0);
}

// ** Выполнение функции PWD ** //

void	pwd_command(char *str)
{
	char *print_pwd;
	char **check;

	check = ft_split(str, ' ');
	print_pwd = malloc(sizeof(char) * 200);
	getcwd(print_pwd, 190);
	if (check[1] && (ft_strncmp(check[1], "-", 1) == 0))
	{
		if ((ft_strncmp(check[1], "-L\0", 3) == 0) || (ft_strncmp(check[1], "-P\0", 3) == 0) ||
				(ft_strncmp(check[1], "-LP\0", 4) == 0))
			printf("%s\n", print_pwd);
		else
			printf("pwd: usage: pwd [-LP]\n");
	}
	else
		printf("%s\n", print_pwd);
	free(print_pwd);
	free_str(check);
}

// ** Выполнение функции ECHO ** //

void	echo_command(char *str)
{
	char **check;

	check = ft_split(str, ' ');
	if (check[1])
	{
		if (ft_strncmp(check[1], "-n\0", 2) == 0)
		{
			if (check[2])
				printf("%s", check[2]);
		}
	}
	else
		printf("\n");
	free_str(check);
}

// ** ENV ** //

void	b_env(char **envp)
{
	size_t	i;

	i = 0;
	while(envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}