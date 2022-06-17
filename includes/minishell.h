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

typedef struct s_data
{
	int	flag_path;
	int pid_main;
}				t_data;

void	ft_loop_shell(char *str, char **envp, t_data *data);
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

char	*ft_string(char *str);
int		check_count_c(char *str);
char	*ft_sep_str(char *str, char c, int flag);
int		ft_len_short(char *str, char c);
char	*ft_substr_mini(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_pars(char const *s1, char const *s2);

#endif