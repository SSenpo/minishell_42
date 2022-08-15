/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:41:24 by mmago             #+#    #+#             */
/*   Updated: 2022/08/15 20:29:32 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/global.h"

// ** -------- add function -------- ** //

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
	int		i;
	int		o;

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

// ** --- FIND LEN OF SEPARATED STR (" or ') --- ** //

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

// ** ------------------------------------- ** //

void	ft_data_null(t_data *data)
{
	data->get_string = NULL;
	data->flag_path = 0;
	data->flag = 0;
	data->get_pipe = 0;
	data->check_pipe_flag = 0;
	data->pipe_flag = 0;
	data->pipe_fork = 0;
	data->num_pipe = 0;
	data->i = 0;
	data->stop_procces = -1;
	data->redir_out_flag = 0;
	data->redir_out_plus = 0;
	data->redir_in_flag = 0;
	data->duble_redirect_flag = 0;
	data->redir_in_str = NULL;
	data->redir_out_str = NULL;
	data->file_redir_fd = 0;
	data->std_in_fd = dup(0);
	data->std_out_fd = dup(1);
	data->heredoc_flag = 0;
	data->delimiter = NULL;
	data->if_pipe_and_heredoc_i = -77;
	unlink("estrong_super_heredoc");
}

void	handler_two(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_redisplay();
		*g_status = 1;
	}
}
