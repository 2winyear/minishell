#include "../include/minishell.h"

t_deque	*make_deque(void)
{
	t_deque	*cmd;

	cmd = malloc(sizeof(t_deque));
	if (!cmd)
		return (NULL);
	cmd->header_node.prev_node = NULL;
	cmd->header_node.next_node = &(cmd->tailer_node);
	cmd->tailer_node.prev_node = &(cmd->header_node);
	cmd->tailer_node.next_node = NULL;
	cmd->current_element_count = 0;
	cmd->seperates = ft_split("|,<<,>>,<,>,;",',');
	cmd->seperate_len = 5;
	return (cmd);
}

t_deque_node	*make_deque_node(char **command, char* seperate)
{
	t_deque_node	*new_node;

	new_node = malloc(sizeof(t_deque_node));
	if (!new_node)
		return (NULL);
	new_node->command = command;
	new_node->seperate = seperate;
	return (new_node);
}

void	push_deque(t_deque *cmd, t_deque_node *element)
{
	t_deque_node	*new_node;
	t_deque_node	*curr_node;
	t_deque_node	*prev_node;

	new_node = element;
	curr_node = &(cmd->tailer_node);
	prev_node = cmd->tailer_node.prev_node;
	new_node->prev_node = prev_node;
	new_node->next_node = curr_node;
	prev_node->next_node = new_node;
	curr_node->prev_node = new_node;
	cmd->current_element_count += 1;
}

t_deque_node	*pop_front_deque(t_deque *cmd)
{
	t_deque_node	*return_node;
	t_deque_node	*change_node;

	return_node = cmd->header_node.next_node;
	if (return_node == &(cmd->tailer_node))
		return (NULL);
	change_node = return_node->next_node;
	cmd->header_node.next_node = change_node;
	cmd->current_element_count -= 1;
	return (return_node);
}

void	display_deque(t_deque *cmd)
{
	t_deque_node	*curr_node;
	t_deque_node	*prev_node;
	int				idx;

	prev_node = &(cmd->header_node);
	curr_node = prev_node->next_node;
	while (curr_node != &(cmd->tailer_node))
	{
		idx = -1;
		printf("command : ");
		while (curr_node->command[++idx])
			printf("%s ", curr_node->command[idx]);
		printf("\nseperate : %s\n", curr_node->seperate);
		prev_node = curr_node;
		curr_node = prev_node->next_node;
	}
}

void	delete_deque(t_deque **cmd)
{
	t_deque_node	*curr_node;
	t_deque_node	*prev_node;
	int				idx;

	prev_node = &((*cmd)->tailer_node);
	curr_node = prev_node->prev_node;
	while (curr_node != &((*cmd)->header_node))
	{
		prev_node = curr_node;
		curr_node = prev_node->prev_node;
		delete_deque_node(&(prev_node));
	}
	idx = -1;
	while (++idx < (*cmd)->seperate_len)
		free((*cmd)->seperates[idx]);
	free((*cmd)->seperates);
	free(*cmd);
	*cmd = NULL;
}

void	delete_deque_node(t_deque_node **node)
{
	int	idx;

	idx = -1;
	while ((*node)->command[++idx])
		free((*node)->command[idx]);
	free((*node)->command);
	if ((*node)->seperate)
		free((*node)->seperate);
	free(*node);
	*node = NULL;
}
