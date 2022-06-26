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

// ** Тут будем проверять строку на builtin команды, которые нужно выполнять отдельно ** //

int	get_str(char *str)
{
	char **pars_str;
	int	i;

	i = 0;
	if (!str[i])
		return -1;
	pars_str = ft_split(str, ' ');
	//pars_str = check_split_simb(pars_str);
	i = 0;
	if (pars_str[i])
	{
		if (ft_strncmp(pars_str[0], "cd\0", 3) == 0)
			i = 1;
		if (ft_strncmp(pars_str[0], "pwd\0", 4) == 0)
			i = 2;
		if (ft_strncmp(pars_str[0], "echo\0", 5) == 0)
			i = 3;
		if (ft_strncmp(pars_str[0], "unset\0", 6) == 0)
			i = 4;
		if (ft_strncmp(pars_str[0], "env\0", 4) == 0)
			i = 5;
		if (ft_strncmp(pars_str[0], "export\0", 4) == 0)
			i = 6;
	}
	free_str(pars_str);
	return (i);
}

char	*ft_check_dollar(char *str, char **envp)
{
	int		i;
	int		count;
	int		start;
	int		flag;

	i = 0;
	count = 0;
	start = 0;
	flag = 0;
	while (str[i] && str[i] != 36)
		i++;
	if (str[i] && str[i] == 36)
	{
		start = i;
		flag = 1;
		count = ft_dollar_count(str, count, i);
		if (count < 1)
			return (str);
	}
	if (flag == 1)
		str = ft_change_dollar_one(str, start, count, envp);
	return (str);
}

int		ft_dollar_count(char *str, int count, int i)
{
	if (str[i + 1] > 47 && str[i + 1] < 58)
	{
		count++;
		i = -2;
	}
	while (str[++i])
	{
		if ((str[i] > 64 && str[i] < 91) ||
			(str[i] > 96 && str[i] < 123) ||
			(str[i] > 47 && str[i] < 58))
			count++;
		else
			break ;
	}
	return (count);
}

// **			RABOTAET			** //

char	*ft_change_dollar_one(char *str, int start, int count, char **envp)
{
	char	**new_string;
	char	*str_env;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	str_env = ft_substr(str, start + 1, count);
	tmp = ft_strjoin(str_env, "=");
	len = ft_strlen(tmp);
	while (envp[i] && (ft_strnstr(envp[i], tmp, len) == 0))
		i++;
	free(tmp);
	free(str_env);
	if (!envp[i])
	{
		tmp = ft_substr(str, 0, start);
		str_env = ft_substr_mini(str, start + count + 1, ft_strlen(str) - len);
		str = ft_strjoin_pars(tmp, str_env);
		str = ft_check_dollar(str, envp);
		return (str);
	}
	new_string = ft_split(envp[i], '=');
	str_env = ft_strdup(new_string[1]);
	free_str(new_string);
	str = ft_change_dollar_two(str, str_env, start, count);
	str = ft_check_dollar(str, envp);
	return (str);
}

char	*ft_change_dollar_two(char *str, char *new_str, int start, int count)
{
	char *full;
	int	i;
	int n;

	i = -1;
	full = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(new_str) - count + 1));
	if (!full)
		return (NULL);
	while (++i < start)
		full[i] = str[i];
	n = -1;
	while (new_str[++n])
		full[i++] = new_str[n];
	while (str[start + count + 1])
	{
		full[i++] = str[start + count + 1];
		count++;
	}
	free(new_str);
	free(str);
	full[i] = '\0';
	return (full);	
}

// **			RABOTAET			** //