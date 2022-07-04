#include "../../includes/minishell.h"

// ** ------------------- CHECK STR FOR (" ' $) ---------------- ** //

char	*ft_string(char *str, char **envp, t_data *data)
{
	char	*new_str;
	char	*get;

	data->flag = check_count_c(str);
	new_str = ft_strdup("");
	get = ft_strdup("");
	if (data->flag < 0)
		str = ft_check_dollar(str, envp, data);
	else
		str = ft_check_dollar_mini(str, 0, envp, data);
	while (data->flag > 0)
	{
		if (data->flag == 1)
		{
			if (ft_len_short(str, 39) == 0)
				str = ft_substr_mini(str, 2, ft_strlen(str) - 2);
			else
			{
				get = ft_sep_str(str, 39, 0, envp, data);
				new_str = ft_strjoin_pars(new_str, get);
				str = ft_substr_mini(str, ft_len_short(str, 39) + 2,
					ft_strlen(str) - ft_len_short(str, 39));
			}
		}
		if (data->flag == 2)
		{
			if (ft_len_short(str, 34) == 0)
				str = ft_substr_mini(str, 2, ft_strlen(str) - 2);
			else
			{
				get = ft_sep_str(str, 34, 0, envp, data);
				new_str = ft_strjoin_pars(new_str, get);
				str = ft_substr_mini(str, ft_len_short(str, 34) + 2,
					ft_strlen(str) - ft_len_short(str, 34));
			}
		}
		data->flag = check_count_c(str);
	}
	new_str = ft_strjoin_pars(new_str, str);
	return (new_str);
}

// ** ------------------- CHECK COUNT " OR ' ---------------- ** //

int	check_count_c(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == 39 && str[++i])
		{
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] && str[i] == 39)
				return (1);
		}
		if (str[i] == 34 && str[++i])
		{
			while (str[i] && str[i] != 34)
				i++;
			if (str[i] && str[i] == 34)
				return (2);
		}
		i++;
	}
	return (-1);
}

// ** ------------------- SEPARATE THE PART OF (' ' or " ") STR ---------------- ** //

char	*ft_sep_str(char *str, char c, int flag, char **envp, t_data *data)
{
	char *str_new;
	int	i;
	int	count;
	int	byte;

	i = 0;
	byte = ft_len_short(str, c);
	str_new = malloc(sizeof(char) * (byte + 1));
	count = 2;
	while (str[flag] && count > 0)
	{
		if (str[flag] == c)
		{
			count--;
			flag++;
		}
		else if (str[flag] == ' ' || str[flag] != c)
		{
			if (str[flag] == ' ' && count == 1)
			{
				str_new[i++] = '\a';
				flag++;
			}
			else
				str_new[i++] = str[flag++];	
		}
	}
	str_new[i] = '\0';
	if (str_new && c == 34)
		str_new = ft_check_dollar(str_new, envp, data);
	return (str_new);
}

// ** ------------------- FIND LEN OF SEPARATED STR (" or ') ---------------- ** //

int	ft_len_short(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 2;
	while (str[i] && count > 0)
	{
		if (str[i] == c)
			count--;
		i++;
	}
	i -= 2;
	return (i);
}
