#include "../includes/minishell.h"

// ** Выполнение функции EXIT ** //

int	ft_exit_print(char *str)
{
	char	**s;
	int		status_exit;

	status_exit = 0;
	s = ft_split(str, ' ');
	if (s[1])
		status_exit = ft_atoi(s[1]);
	exit(status_exit);
}

int	ft_change_status(int status)
{
	if (status > 0)
		status /= 256;
	return (status);
}