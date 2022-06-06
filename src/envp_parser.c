#include "../includes/minishell.h"

// ** Для поиска текущего каталога, после выполнения CD ** //

char	**find_pwd(char **envp)
{
	char	*new_pwd;
	char	**old_pwd;
	int		i;
	int		o;

	i = 0;
	while (ft_strnstr(envp[i], "PWD", 3) == 0)
		i++;
	o = 0;
	old_pwd = ft_split(envp[i], '=');
	new_pwd = malloc(1000);
	getcwd(new_pwd, 150);
	envp[i] = ft_strjoin("PWD=", new_pwd);
	envp[i + 1] = ft_strjoin("OLDPWD=", old_pwd[1]);
	i = 0;
	free(new_pwd);
	free(old_pwd[0]);
	free(old_pwd[1]);
	free(old_pwd);
	return (envp);
}

// ** Тут будем проверять строку на builtin команды, которые нужно выполнять отдельно ** //

int	get_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (ft_strncmp(&str[i], "cd", 2) == 0)
	{
		return (1);
	}
	return (0);
}

// ** Выполнение функции CD ** //

int cd(char *str)
{
	char **new_str;

	new_str = ft_split(str, ' ');
	if (chdir(new_str[1]) != 0)
	{
		write(2, "Error: Fail cd\n", 15);
		return (1);
	}
	return (0);
}