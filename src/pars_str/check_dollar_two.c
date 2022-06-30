#include "../../includes/minishell.h"

// ** ----------------------------------------------------- ** //

char	*ft_check_dollar_mini(char *str, int i, char **envp, t_data *data)
{
	char	c;

	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
				return (str);
			i++;
		}
		else if (str[i] == 36 && str[++i])
		{
			if (str[i] == 34 || str[i] == 39)
				str[i - 1] = ' ';
			else
				str = ft_first_check_doll(str, envp, data, (i - 1));
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

char	*ft_first_check_doll(char *str, char **envp, t_data *data, int i)
{
	int		count;
	int		start;

	count = 0;
	start = 0;
	if (str[i] && str[i] == 36)
	{
		start = i;
		count = ft_dollar_count(str, count, i);
		if (count == -1)
		{
			str = dollar_question(str, data, i);
			str = ft_check_dollar_mini(str, 0, envp, data);
		}
		else if (count < 1)
			return (str);
		else
			str = ft_first_change_doll(str, start, count, envp, data);
	}
	return (str);
}

int		ft_dollar_count(char *str, int count, int i)
{
	if (str[i + 1] > 47 && str[i + 1] < 58)
	{
		count++;
		i = -2;
	}
	else if (str[i + 1] == 63 || str[i + 1] == 36)
	{
		count = -1;
		return (count);
	}
	while (str[++i])
	{
		if ((str[i] > 64 && str[i] < 91) ||
			(str[i] > 96 && str[i] < 123) ||
			(str[i] > 47 && str[i] < 58) ||
			(str[i] == 95))
			count++;
		else
			break ;
	}
	return (count);
}

char	*dollar_question(char *str, t_data *data, int i)
{
	char	*new_str;
	char	*str_pid;
	int		start;
	int		child_pid;

	start = -1;
	if (str[++i] == 36)
		child_pid = getpid();
	else if (str[i] == 63)
		child_pid = data->status;
	else
		return (str);
	str_pid = ft_itoa(child_pid);
	child_pid = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(str_pid)));
	while (str[++start])
	{
		if (start == (i - 1))
		{
			while (str_pid[child_pid])
				new_str[start++] = str_pid[child_pid++];
			while (str[++i])
				new_str[start++] = str[i];
			free(str_pid);
			free(str);
			new_str[start] = '\0';
			return (new_str);
		}
		else
			new_str[start] = str[start];
	}
	return (new_str);
}

char	*ft_first_change_doll(char *str, int start, int count, char **envp, t_data *data)
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
		str = ft_check_dollar_mini(str, 0, envp, data);
		return (str);
	}
	new_string = ft_split(envp[i], '=');
	str_env = ft_strdup(new_string[1]);
	free_str(new_string);
	str = ft_change_dollar_two(str, str_env, start, count);
	str = ft_check_dollar_mini(str, 0, envp, data);
	return (str);
}

// ** ----------------------------------------------------- ** //