#include "../../includes/minishell.h"

char	*ft_string(char *str)
{
	char	*new_str;
	char	*get;
	int		i;
	int		flag;

	flag = check_count_c(str);
	i = 0;
	new_str = ft_strdup("");
	get = ft_strdup("");
	while (flag > 0)
	{
		if (flag == 1)
		{
			if (ft_len_short(str, 39) == 0)
				str = ft_substr_mini(str, 2, ft_strlen(str) - 2);
			else
			{
				get = ft_sep_str(str, 39, 0);
				new_str = ft_strjoin_pars(new_str, get);
				str = ft_substr_mini(str, ft_len_short(str, 39) + 2,
					ft_strlen(str) - ft_len_short(str, 39));
			}
		}
		if (flag == 2)
		{
			if (ft_len_short(str, 34) == 0)
				str = ft_substr_mini(str, 2, ft_strlen(str) - 2);
			else
			{
				get = ft_sep_str(str, 34, 0);
				new_str = ft_strjoin_pars(new_str, get);
				str = ft_substr_mini(str, ft_len_short(str, 34) + 2,
					ft_strlen(str) - ft_len_short(str, 34));
			}
		}
		if (flag == 0)
			new_str = ft_strjoin_pars(new_str, str);
		flag = check_count_c(str);
	}
	new_str = ft_strjoin_pars(new_str, str);
	return (new_str);
}

int	check_count_c(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			while (str[i] && str[i] != 39)
				i++;
			if (str[i])
				return (1);
			return (-1);
		}
		if (str[i] == 34)
		{
			while (str[i] && str[i] != 34)
				i++;
			if (str[i])
				return (2);
			return (-1);
		}
		i++;
	}
	return (0);
}

char	*ft_sep_str(char *str, char c, int flag)
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
		else
			str_new[i++] = str[flag++];
	}
	str_new[i] = '\0';
	return (str_new);
}

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

char	*ft_substr_mini(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		str = (char *)malloc(len + 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (len > i)
		*(str + i++) = *(s + start++);
	if (s)
		free((void *)s);
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_pars(char const *s1, char const *s2)
{
	char	*s3;
	int	i;
	int	o;

	if (!s1 && !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	i = -1;
	o = -1;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++o])
	{
		s3[i] = s2[o];
		i++;
	}
	s3[i] = '\0';
	if (s1)
		free((void *)s1);
	if (s2)
		free((void *)s2);
	return (s3);
}