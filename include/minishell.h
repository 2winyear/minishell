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

# include "../parsing/deque.h"

#define FALSE 0
#define TRUE 1
#define ERROR -1
#define CURSE_POS "\033[6n"
#define EOF_CMD 4
#define BACKSPACE 127

///////////////parsing/////////////
char            **ft_split(char const *s, char c);
int				is_seperate(char *line, char **seperate);
int				save_command(deque *cmd, char *command, char *seperate, int len);
int				is_double_quote(char word);
int				tokenizing(deque *cmd, char *command);
deque			*parsing(char *command);


///////////////signal//////////////
void            sig_handler(int signum);
void            init_signal(void);


///////////////read////////////////
int             my_bind_esc(int count, int key);
char            *read_line(void);

///////////////init////////////////
void            display_logo(void);

///////////////env_util////////////

///////////////util////////////////
int             ft_isdigit(int c);
int             ft_strlen(char *str);
int             ft_atoi(char *str);
int             ft_nbrlen(int num);
int             ft_strncmp(char *str1, char *str2, int n);
char            *ft_strncpy(char *line, int n);
char	        *ft_strnstr(const char *b, const char *l, size_t len);
char	        *ft_strdup(char *s1);
char            *ft_strndup(char *s1, int len);

//////////////minishell////////////
//char            *execute(command_node *command);
//int             interpret(command_node *commands);
void            inf_loop(void);

#endif
// 컴파일할때 뒤에 -lreadline
// 클러스터에서 사용하는 건 clang = gcc
