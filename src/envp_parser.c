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
	new_pwd = malloc((sizeof(char) * 200));
	getcwd(new_pwd, 150);
	envp[i] = ft_strjoin("PWD=", new_pwd);
	envp[i + 1] = ft_strjoin("OLDPWD=", old_pwd[1]);
	i = 0;
	free(new_pwd);
	free_str(old_pwd);
	return (envp);
}

// ** Тут будем проверять строку на builtin команды, которые нужно выполнять отдельно ** //

int	get_str(char *str)
{
	char **pars_str;
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (!str[i])
		return (-1);
	pars_str = ft_split(str, ' ');
	i = 0;
	// if (ft_strncmp(&str[i], "cd", 2) == 0)
	if (pars_str[i])
	{
		if (ft_strncmp(pars_str[0], "cd", 2) == 0)
			i = 1;
		// if (ft_strncmp(&str[i], "pwd", 3) == 0)
		if (ft_strncmp(pars_str[0], "pwd", 3) == 0)
			i = 2;
	}
	free_str(pars_str);
	return (i);
}