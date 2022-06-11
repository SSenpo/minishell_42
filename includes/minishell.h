#ifndef MINISHEL_H
# define MINISHEL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

int		cd(char *str);
void	b_env(char **envp);
void	free_str(char **str);
char	*clean_str(char *str);
int		get_str(char *str);
char	**find_pwd(char **envp);
void	pwd_command(char *str);
void	echo_command(char *str);
char	**built_cmd(char *str, int r, char **envp);
char	**malloc_envp(char **envp);
char	**b_unset(char *str, char **envp);
char	**del_var(char *str, char **envp);

// char	*clean_str(char *str);
// char	*sep_str(char *str, char c);

#endif