#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>

# include <termios.h>
# include <term.h>

# include "deque.h"

# define FALSE 0
# define TRUE 1
# define ERROR -1
# define BUF_SIZE 1025

extern int rl_catch_signals;
extern void rl_replace_line(const char *text, int n);

typedef struct s_infomation
{
	t_deque		*cmd;
	char		**env;
	char		*oldpwd;
	char		*pwd;
	char		*home;
	int			env_size;
	int			is_pipe;
	int			is_prev_pipe;
	int			status;
}	t_info;

///////////////command_util///////////
char			*find_conv_dallor(char *command, t_info *info);
char			*div_dup(char *command, t_info *info);
char			**set_split_cmd(t_info *info, char *command);
int				save_command(t_info *info, char *command, \
		int spt_type, int len);
int				space_count(char *command);
char			*add_word(char **result, char word);
char			*conv_dallor(char *result, char *command, int len, t_info *info);

///////////////parsing/////////////
char			**ft_split(char const *s, char c);
int				is_seperate(char *line, char **seperate);
int				is_double_quote(char word);
void			change_command(t_deque *cmd);
int				tokenizing(t_info *info, char *command);
int				parsing(char *command, t_info *info);

///////////////signal//////////////
///////////////read////////////////
void			sig_handler(int signum);
void			init_signal(void);
char			*read_line(t_info *info);

///////////////init////////////////
void			display_logo(t_info *info);
void			*free_info(t_info **info);
t_info			*init_info(char **env);

///////////////util////////////////
int				ft_isdigit(int c);
int				ft_strlen(char *str);
int				ft_atoi(char *str);
int				ft_nbrlen(int num);
int				ft_strcmp(char *str1, char *str2);
int				ft_strncmp(char *str1, char *str2, int n);
char			*ft_strncpy(char *line, int n);
char			*ft_strnstr(const char *b, const char *l, size_t len);
char			*ft_strdup(char *s1);
char			*ft_strndup(char *s1, int len);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjointri(char *str1, char *str2, char *str3);
char			*ft_itoa(int n);

//////////////env_util/////////////
void			*free_matrix(char ***env);
char			**env_dup(char **env, int flag, char *app_str);
char			**find_bin_path(char **env);
char			*make_bin_path(char **env, char *cmd, char **path);
char			*find_env_value(t_info *info, char *key);

//////////////pipe_func////////////
void			run_single_cmd(t_info *info);
int				check_run_builtin(char **command, t_info *info);
void			act_child(t_deque_node *node, t_info *info);
void			operate_pipe(t_deque *cmd, t_deque_node *node, int flag);

//////////////redirection_func/////
int				check_run_redirection(t_deque_node *node);
void			overwrite_file(t_deque_node *node);
void			append_file(t_deque_node *node);
void			send_file(t_deque_node *node);
void			send_doc(t_deque_node *node);

//////////////cmd//////////////////
int				ft_cd(char **command, t_info *info);
void			ft_export(char **command, t_info *info);
int				ft_unset(char **command, t_info *info);
void			ft_exit(char **command, t_info *info);
void			ft_echo(char **command);

//////////////minishell////////////
int				execute(t_info *info);
void			inf_loop(t_info *info);

#endif
