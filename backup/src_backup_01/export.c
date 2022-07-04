#include "../includes/minishell.h"

// ** Export - добавляем что-то в ENVP ** //

char    **exec_export(char *str, char **envp)
{
    char	**new_str;
    int		i;

    i = 0;
	new_str = ft_split(str, ' ');
	if (new_str[1] && (ft_strnstr(new_str[1], "-p\0", 3) != 0))
	{
		while (envp[i])
		{
			printf("declare -x %s\n", envp[i]);
			i++;
		}
		i = 0;
	}
	else
	{
    	while (envp[i] &&
			ft_strnstr(envp[i], new_str[1], ft_strlen(new_str[1])) == 0)
			i++;
		if (!envp[i])
			envp = get_export(new_str[1], envp, i);
	}
	return (envp);
}

char	**get_export(char *str, char **envp, int i)
{
	char	**new_envp;
	int		s;

	s = -1;
	new_envp = malloc(sizeof(char *) * (i));
	while (envp[++s])
		new_envp[s] = ft_strdup(envp[s]);
	new_envp[s] = ft_strdup(str);
	new_envp[s + 1] = NULL;
	free_str(envp);
	return (new_envp);
}

// ** PRINT ENV ** //

void	b_env(char **envp)
{
	int	i;

	i = -1;
	while(envp[++i])
		printf("%s\n", envp[i]);
}