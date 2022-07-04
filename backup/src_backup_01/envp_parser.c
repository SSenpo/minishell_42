#include "../includes/minishell.h"

// ** ENVP маллочим и перезаписываем ** //

char	**malloc_envp(char **envp)
{
	char	**envp_1;
	int		i;
	int		o;

	i = -1;
	o = -1;
	while (envp[++i]);
	envp_1 = malloc(sizeof(char *) * (i + 1));
	envp_1[i + 1] = NULL;
	i = -1;
	while (envp[++i])
	{
		while (envp[i][++o]);
		envp_1[i] = malloc(sizeof(char) * (o + 1));
		envp_1[i][o + 1] = '\0';
		o = 0;
		while (envp[i][o])
		{
			envp_1[i][o] = envp[i][o];
			o++;
		}
		o = -1;
	}
	return (envp_1);
}

// ** ENVP перезаписываем путь после CD ** //

char	**find_pwd(char **envp)
{
	char	*new_pwd;
	char	**old_pwd;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PWD", 3) == 0)
		i++;
	if (!envp[i])
		return (envp);
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
