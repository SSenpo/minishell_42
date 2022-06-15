#include "../includes/minishell.h"

// ** ** //
// char	*clean_str(char *str)
// {
// 	char	*join;

// 	join = NULL;
// 	if (str[0])
// 	{
// 		if (count_c(str, 34) > 0 && count_c(str, 34) % 2 == 0)
// 		{
// 			join = sep_str(str, 34);
// 			return (join);
// 		}
// 		else if (count_c(str, 39) > 0 && count_c(str, 39) % 2 == 0)
// 		{
// 			join = sep_str(str, 39);
// 			return (join);
// 		}
// 		else if ((count_c(str, 39) > 0 && count_c(str, 39) % 2 != 0) ||
// 					(count_c(str, 34) > 0 && count_c(str, 34) % 2 != 0))
// 			return (join);
// 		else
// 			return (str);
// 	}
// 	return (str);
// }

// char	*sep_str(char *str, char c)
// {
// 	char	*new_str;
// 	int		i;
// 	int		n;
// 	int		count;

// 	i = -1;
// 	count = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] == c)
// 			count++;
// 	}
// 	new_str = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
// 	i = 0;
// 	n = 0;
// 	while (str[i])
// 		(str[i] != c) ? (new_str[n++] = str[i++]) : (i++);
// 	free(str);
// 	new_str[n] = '\0';
// 	return (new_str);
// }

// int	count_c(char *str, char c)
// {
// 	int	i;
// 	int	count;

// 	i = -1;
// 	count = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] == c)
// 			count++;
// 	}
// 	return (count);
// }