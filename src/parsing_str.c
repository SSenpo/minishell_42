#include "../includes/minishell.h"

// ** ** //
// char	*clean_str(char *str)
// {
// 	int	i;
	
// 	i = 0;
// 	if (str[0] == 39)
// 		return (sep_str(str, 39));
// 	if (str[0] == 34)
// 	{
// 		str = sep_str(str, 39);
// 		return (sep_str(str, 34));
// 	}
// 	else
// 		return (str);
// }

// char	*sep_str(char *str, char c)
// {
// 	char	*new_str;
// 	int		i;
// 	int		n;
// 	int		count;

// 	i = -1;
// 	count = 9;
// 	while (str[++i])
// 	{
// 		if (str[i] == c)
// 			count++;
// 	}
// 	new_str = malloc(sizeof(char) * (ft_strlen(str) - count));
// 	i = 0;
// 	n = 0;
// 	while (str[i])
// 		(str[i] != c) ? (new_str[n++] = str[i++]) : (i++);
// 	free(str);
// 	// new_str[n] = '\0';
// 	return (new_str);
// }