#ifndef	QUEUE_H
# define QUEUE_H

# define TRUE 1
# define FALSE 0

# include "../include/minishell.h"

typedef struct				s_deque_node
{
	char					*seperate;
	char					**command;
	int						pipe[2];
	struct s_deque_node		*prev_node;
	struct s_deque_node		*next_node;
} t_deque_node;

typedef struct				s_deque_type
{
	t_deque_node			header_node;
	t_deque_node			tailer_node;
	int						current_element_count;
	char					**seperates;
	int						seperate_len;
} t_deque;

t_deque						*make_deque(void);

t_deque_node				*make_deque_node(char **command, char* seperate);

void						push_deque(t_deque *cmd, t_deque_node *element);

t_deque_node				*pop_front_deque(t_deque *cmd);

void						display_deque(t_deque *cmd);

void						delete_deque(t_deque **cmd);

void						delete_deque_node(t_deque_node **node);

#endif
