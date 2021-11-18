#include "../include/minishell.h"

deque	*make_deque(void)
{
	deque	*cmd;

	cmd = malloc(sizeof(deque));
	if (!cmd)
		return (NULL);
	cmd->header_node.prev_node = NULL;
	cmd->header_node.next_node = &(cmd->tailer_node);
	cmd->tailer_node.prev_node = &(cmd->header_node);
	cmd->tailer_node.next_node = NULL;
	cmd->current_element_count = 0;
	cmd->seperates = ft_split("|,<<,>>,<,>",',');
	cmd->seperate_len = 5;
	return (cmd);
}

deque_node	*make_deque_node(char *command, char* seperate)
{
	deque_node	*new_node;

	new_node = malloc(sizeof(deque_node));
	if (!new_node)
		return (NULL);
	new_node->command = command;
	new_node->seperate = seperate;
	return (new_node);
}

void	push_deque(deque *cmd, deque_node *element)
{
	deque_node	*new_node;
	deque_node	*curr_node;
	deque_node	*prev_node;

	new_node = element;
	curr_node = &(cmd->tailer_node);
	prev_node = cmd->tailer_node.prev_node;
	new_node->prev_node = prev_node;
	new_node->next_node = curr_node;
	prev_node->next_node = new_node;
	curr_node->prev_node = new_node;
	cmd->current_element_count += 1;
}

deque_node	*pop_front_deque(deque *cmd)
{
	deque_node	*return_node;
	deque_node	*change_node;

	return_node = cmd->header_node.next_node;
	if (return_node == &(cmd->tailer_node))
		return (NULL);
	change_node = return_node->next_node;
	change_node->prev_node = NULL;
	cmd->header_node.next_node = change_node;
	return (return_node);
}

void	display_deque(deque *cmd)
{
	deque_node	*curr_node;
	deque_node	*prev_node;

	prev_node = &(cmd->header_node);
	curr_node = prev_node->next_node;
	while (curr_node != &(cmd->tailer_node))
	{
		printf("command : %s\nseperate : %s\n", curr_node->command, curr_node->seperate);
		prev_node = curr_node;
		curr_node = prev_node->next_node;
	}
}

void	delete_deque(deque *cmd)
{
	deque_node	*curr_node;
	deque_node	*prev_node;
	int			idx;

	prev_node = &(cmd->header_node);
	curr_node = prev_node->next_node;
	while (curr_node != &(cmd->tailer_node))
	{
		prev_node = curr_node;
		curr_node = prev_node->next_node;
		if (prev_node->command)
			free(prev_node->command);
		if (prev_node->seperate)
			free(prev_node->seperate);
		free(prev_node);
	}
	idx = -1;
	while (++idx < cmd->seperate_len)
		free(cmd->seperates[idx]);
	free(cmd->seperates);
	free(cmd);
}
