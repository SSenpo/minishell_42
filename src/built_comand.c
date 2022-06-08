#include "../includes/minishell.h"

// ** Определяем билд команду ** //

void	built_cmd(char *str, int r)
{
	// printf("test1\n");
	if (r == 1)
		cd(str);
	if (r == 2)
		pwd_command();
	// if (r == 3)
	// 	echo;
	// if (r == 4)
	// if (r == 5)
	// if (r == 6)
}

// ** Выполнение функции CD ** //

int cd(char *str)
{
	char **new_str;

	// printf("test_cd\n");
	new_str = ft_split(str, ' ');
	if (new_str[1])
	{
		if (chdir(new_str[1]) != 0)
		{
			// write(2, "Error: Fail cd\n", 15);
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

void	pwd_command()
{
	char *print_pwd;

	// printf("test_pwd\n");
	print_pwd = malloc(sizeof(char) * 200);
	getcwd(print_pwd, 190);
	printf("%s\n", print_pwd);
	free(print_pwd);
}
