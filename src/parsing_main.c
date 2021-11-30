#include "../include/minishell.h"

int	is_seperate(char *line, char **seperate)
{
	int	idx;

	idx = -1;
	while (seperate[++idx])
	{	
		if (!ft_strncmp(line, seperate[idx], ft_strlen(seperate[idx])))
			return (idx);
	}
	return (-1);
}

int	is_double_quote(char word)
{
	static int	flag;

	if (flag == 1 && word == '"')
		flag = 0;
	else if (word == '"')
		flag = 1;
	if (!flag)
		return (1);
	return (0);
}

int	tokenizing(t_info *info, char *command)
{
	int		start;
	int		end;
	int		sep_idx;

	start = 0;
	end = -1;
	while (command[++end])
	{
		if (is_double_quote(command[end]))
		{
			sep_idx = is_seperate(command + end, info->cmd->seperates);
			if (sep_idx != -1)
			{
				if (!save_command(info, command + start, \
						sep_idx, end - start))
					return (0);
				start = end + ft_strlen(info->cmd->seperates[sep_idx]);
				end = start - 1;
			}
		}
	}
	if (end - start != 0 && \
			!save_command(info, command + start, -1, end - start))
		return (0);
	return (1);
}

void	change_command(t_deque *cmd)
{
	t_deque_node	*temp_node;
	char			**temp;

	temp_node = cmd->header_node.next_node;
	while (temp_node != &(cmd->tailer_node))
	{
		if (temp_node->next_node != &(cmd->tailer_node) && \
				(temp_node->spt_type == 3 || temp_node->spt_type == 5))
		{
			temp = temp_node->command;
			temp_node->command = temp_node->next_node->command;
			temp_node->next_node->command = temp;
		}
		temp_node = temp_node->next_node;
	}
}

int	parsing(char *command, t_info *info)
{
	if (!command)
		return (0);
	info->cmd = make_deque();
	if (!info->cmd)
		return (0);
	if (!tokenizing(info, command))
	{
		printf("tokenizing ERROR\n");
		delete_deque(&(info->cmd));
		return (0);
	}
	change_command(info->cmd);
	return (1);
}
