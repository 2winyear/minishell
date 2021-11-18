#ifndef	QUEUE_H
# define QUEUE_H

# define TRUE 1
# define FALSE 0

# include "../include/minishell.h"

typedef struct				deque_node_type
{
	char					*seperate;
	char					*command;
	struct deque_node_type	*prev_node;
	struct deque_node_type	*next_node;
} deque_node;

typedef struct				deque_type
{
	deque_node				header_node;
	deque_node				tailer_node;
	int						current_element_count;
	char					**seperates;
	int						seperate_len;
} deque;

deque						*make_deque(void);

deque_node					*make_deque_node(char *command, char* seperate);

void						push_deque(deque *cmd, deque_node *element);

deque_node					*pop_front_deque(deque *cmd);

void						display_deque(deque *cmd);

void						delete_deque(deque *cmd);

#endif
