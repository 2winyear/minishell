#include "../include/minishell.h"

int	is_seperate(char *line, char **seperate)
{
	int idx;

	idx = -1;
	while (seperate[++idx])
	{	
        if (!ft_strncmp(line, seperate[idx], ft_strlen(seperate[idx])))
            return (idx);
    }
	return (-1);
}

int	save_command(t_deque *cmd, char *command, char *seperate, int len)
{
	char		*temp;
	char		**split_cmd;
	char		*temp_spr;
	t_deque_node	*new_node;

	temp = ft_strndup(command, len);
	if (!temp)
		return (0);
	split_cmd = ft_split(temp, ' ');
	free(temp);
	if (!split_cmd)
		return (0);
	temp_spr = ft_strdup(seperate);
	new_node = make_deque_node(split_cmd, temp_spr);
	if (!new_node)
		return (0);
	push_deque(cmd, new_node);
	return (1);
}

int is_double_quote(char word)
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

int	tokenizing(t_deque *cmd, char *command)
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
			sep_idx = is_seperate(command + end, cmd->seperates);
			if (sep_idx != -1)
			{
			    if (!save_command(cmd, command + start, cmd->seperates[sep_idx], end - start))
				 	return (0);
				start = end + ft_strlen(cmd->seperates[sep_idx]);
				end = start - 1;
			}
        }
	}
	if (end - start != 0 && !save_command(cmd, command + start, NULL, end - start))
		return (0);
    return (1);
}

t_deque	*parsing(char *command)
{
	t_deque	*cmd;

	cmd = make_deque();
	if (!cmd)
		return (NULL);
	if (!tokenizing(cmd, command))
	{
		printf("tokenizing ERROR\n");
		free(cmd);
		return (NULL);
	}
	return(cmd);
}
