/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:40:54 by mmago             #+#    #+#             */
/*   Updated: 2022/08/15 20:07:36 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ** ------------------- CHECK STR FOR (" ' $) ---------------- ** //

char	*ft_string(char *str, t_data *data)
{
	char	*new_str;
	char	*get;

	data->flag = check_count_c(str);
	new_str = ft_strdup("");
	get = NULL;
	data->get_string = ft_strdup(str);
	free(str);
	if (data->flag < 0)
		data->get_string = ft_check_dollar(data->get_string, data);
	else
		data->get_string = ft_check_dollar_mini(data->get_string, 0, data);
	while (data->flag > 0)
	{
		if (data->flag == 1)
			data->get_simb = 39;
		else
			data->get_simb = 34;
		new_str = get_str_part_two(get, new_str, data);
		data->flag = check_count_c(data->get_string);
	}
	new_str = ft_strjoin_pars(new_str, data->get_string);
	ft_check_str_for_pipe(new_str, data);
	return (new_str);
}

char	*get_str_part_two(char *get, char *new_str, t_data *data)
{
	if (ft_len_short(data->get_string, data->get_simb) == 0)
	{
		data->get_string = ft_substr_mini(data->get_string, 2,
				ft_strlen(data->get_string) - 2);
	}
	else
	{
		if (get)
			free(get);
		get = ft_sep_str(data->get_string, data->get_simb, 0, data);
		new_str = ft_strjoin_pars(new_str, get);
		data->get_string = ft_substr_mini(data->get_string,
				ft_len_short(data->get_string, data->get_simb) + 2,
				ft_strlen(data->get_string) - ft_len_short(data->get_string,
					data->get_simb));
	}
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

// ** ---- SEPARATE THE PART OF (' ' or " ") STR ---- ** //

char	*ft_sep_str(char *str, char c, int flag, t_data *data)
{
	char	*str_new;
	int		byte;

	byte = ft_len_short(str, c);
	str_new = malloc(sizeof(char) * (byte + 1));
	if (!str_new)
		return (str);
	str_new = ft_sep_str_end(str, flag, c, str_new);
	if (str_new && c == 34)
		str_new = ft_check_dollar(str_new, data);
	return (str_new);
}

char	*ft_sep_str_end(char *str, int flag, char c, char *str_new)
{
	int	count;
	int	i;

	i = 0;
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
	return (str_new);
}
