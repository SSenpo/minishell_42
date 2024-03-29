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
	char	**envp;
	char	**pipe_part_split;
	char	*get_string;
	char	get_simb;
	int		pid_child;
	int		flag_path;
	int 	pid_main;
	int		flag;
	int		status;
	int		get_pipe;
	int		**fd_pipe;
	int		check_pipe_flag;
	int		pipe_flag;
	int		redir_out_flag;
	int		redir_out_plus;
	char	*redir_out_str;
	int		redir_in_flag;
	char	*redir_in_str;
	int		file_redir_fd;
	int		heredoc_flag;
	int		if_pipe_and_heredoc_i;
	char	*delimiter;
	int		std_in_fd;
	int		std_out_fd;
	int		duble_redirect_flag;
	int		pipe_fork;
	int		num_pipe;
	int		i;
	int		stop_procces;
}				t_data;

// ** MAIN ** //
void	ft_start_shell(t_data *data, char **envp);
void	ft_loop_shell(char *str, t_data *data);
char	*ft_do_minishell(char *str, t_data *data);

// ** GET_STR ** //
char	*ft_string(char *str, t_data *data);
char	*ft_sep_str(char *str, char c, int flag, t_data *data);
char	*ft_sep_str_end(char *str, int flag, char c, char *str_new);
char	*get_str_part_two(char *get, char *new_str, t_data *data);
int		check_count_c(char *str);

void	ft_procces_build_in(t_data *data);
void	ft_check_str_for_direct(char *str, t_data *data);
void	ft_redirect_null(t_data *data);

void	ft_do_heredoc(t_data *data);
char	*change_heredoc(char *command_str, t_data *data, int index);

char	*make_redirect(char *command_str, t_data *data);
char	*change_fd_out(char *command_str, t_data *data, int index);
char	*change_fd_in(char *command_str, t_data *data, int index);


int		ft_is_pipe_or_redirect(t_data *data);

void	ft_check_str_for_pipe(char *str, t_data *data);
void	ft_make_a_pipe(char *str, t_data *data);
void	ft_procces(t_data *data);
void	ft_data_null(t_data *data);

void	handler_two(int signum);

char	*get_str_part_two(char *get, char *new_str, t_data *data);

int		ft_dollar_count(char *str, int count, int i);

char	**check_split_simb(char **str);

// ** EXPORT ** //
char    **exec_export(char *str, t_data *data);
char	**get_export(char *str, t_data *data, int i);

// ** EXIT ** //
int		ft_exit_print(char *str);
int		ft_change_status(int status);
int		check_num_or_not(const char *str);

char	*ft_check_dollar(char *str, t_data *data);
char	*ft_change_dollar_one(char *str, int start, int count, t_data *data);
char	*ft_change_dollar_two(char *str, char *new_str, int start, int count);
char	*ft_check_dollar_mini(char *str, int i, t_data *data);
char	*dollar_question(char *str, t_data *data, int i);

char	*ft_first_change_doll(char *str, int start, int count, t_data *data);
char	*ft_first_check_doll(char *str, t_data *data, int i);


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