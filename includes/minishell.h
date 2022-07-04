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

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

typedef struct s_data
{
	char	**envp;
	char	*get_string;
	char	get_simb;
	int		flag_path;
	int 	pid_main;
	int		flag;
	int		status;
	int		get_pipe;
	int		*fd_pipe;
}				t_data;

char	*get_str_part_two(char *get, char *new_str, t_data *data);

int		ft_dollar_count(char *str, int count, int i);

char	**check_split_simb(char **str);

// ** EXPORT ** //
char    **exec_export(char *str, t_data *data);
char	**get_export(char *str, t_data *data, int i);

// ** EXIT ** //
int	ft_exit_print(char *str);
int	ft_change_status(int status);

char	*ft_check_dollar(char *str, t_data *data);
char	*ft_change_dollar_one(char *str, int start, int count, t_data *data);
char	*ft_change_dollar_two(char *str, char *new_str, int start, int count);
char	*ft_check_dollar_mini(char *str, int i, t_data *data);
char	*dollar_question(char *str, t_data *data, int i);

char	*ft_first_change_doll(char *str, int start, int count, t_data *data);
char	*ft_first_check_doll(char *str, t_data *data, int i);

void	ft_loop_shell(char *str, char **envp, t_data *data);
int		cd(char *str);
void	b_env(t_data *data);
void	free_str(char **str);
char	*clean_str(char *str);
int		get_str(char *str);
char	**find_pwd(t_data *data);
void	pwd_command(char *str);
void	echo_command(char *str);
char	**built_cmd(char *str, int r, t_data *data);
char	**malloc_envp(char **envp);
char	**b_unset(char *str, t_data *data);
char	**del_var(char *str, t_data *data);

char	*ft_string(char *str, t_data *data);

int		check_count_c(char *str);

char	*ft_sep_str(char *str, char c, int flag, t_data *data);

int		ft_len_short(char *str, char c);
char	*ft_substr_mini(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_pars(char const *s1, char const *s2);

void	error(void);
char	*find_path(char *command, t_data *data);
void	check_str(char *str, t_data *data);

void	check_str_pipe(char *str, t_data *data);

#endif