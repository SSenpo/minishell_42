#include "../includes/minishell.h"

// ** Unset - удаляем что-то из ENVP ** //

char	**b_unset(char *str, char **envp)
{
	size_t	i;
	char	**new_str;

	i = 0;
	new_str = ft_split(str, ' ');
	while (envp[i] &&
		ft_strnstr(envp[i], new_str[1], ft_strlen(new_str[1])) == 0)
		i++;
	if (envp[i])
		envp = del_var(str, envp);
	else
		printf("shell : unset: `%s': not a valid identifier\n", new_str[1]);
	return (envp);
}

char	**del_var(char *str, char **envp)
{
	size_t	i;

	i = 0;
	str = (ft_split(str, ' '))[1];
	while(envp[i])
	{
		if ((ft_strnstr(envp[i], str, ft_strlen(str)) == 0))
			i++;
		else
			break;
	}
	while (envp[i + 1])
	{
		free(envp[i]);
		envp[i] = ft_strdup(envp[i + 1]);
		i++;
	}
	free(envp[i]);
	envp[i] = NULL;
	return (envp);
}