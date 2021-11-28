#include "../include/minishell.h"

void	delete_deque(t_deque **cmd)
{
	t_deque_node	*curr_node;
	t_deque_node	*prev_node;
	int				idx;

	if (!(*cmd))
		return ;
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

int	save_command(t_deque *cmd, char *command, int spt_type, int len)
{
	char			*temp;
	char			**split_cmd;
	char			*temp_spr;
	t_deque_node	*new_node;

	temp = ft_strndup(command, len);
	if (!temp)
		return (0);
	split_cmd = ft_split(temp, ' ');
	free(temp);
	if (!split_cmd)
		return (0);
	if (spt_type != -1)
		temp_spr = ft_strdup(cmd->seperates[spt_type]);
	else
		temp_spr = NULL;
	new_node = make_deque_node(split_cmd, temp_spr, spt_type);
	if (!new_node)
		return (0);
	push_deque(cmd, new_node);
	return (1);
}
