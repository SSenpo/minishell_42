#include "../includes/minishell.h"

int	ft_exit_print(char *str)
{
	char	**s;
	int		status_exit;

	status_exit = 0;
	s = ft_split(str, ' ');
	if (s[1])
		status_exit = ft_atoi(s[1]);
	printf("STATUS 1 = %d\n", status_exit);
	exit(status_exit);
}