#include "../../includes/minishell.h"

// ** ----------------------------------------------------- ** //

char	*ft_check_dollar(char *str, char **envp, t_data *data)
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
		if (count == -1)
		{
			str = dollar_question(str, data, i);
			str = ft_check_dollar(str, envp, data);
		}
		if (count < 1)
			return (str);
	}
	if (flag == 1)
		str = ft_change_dollar_one(str, start, count, envp, data);
	return (str);
}

char	*ft_change_dollar_one(char *str, int start, int count, char **envp, t_data *data)
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
		str = ft_check_dollar(str, envp, data);
		return (str);
	}
	new_string = ft_split(envp[i], '=');
	str_env = ft_strdup(new_string[1]);
	free_str(new_string);
	str = ft_change_dollar_two(str, str_env, start, count);
	str = ft_check_dollar(str, envp, data);
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

// ** -------------------------------------------------------------------------- ** //
