#include "../include/minishell.h"

int	check_run_builtin(char **command, t_info *info)
{
	if (!ft_strcmp(command[0], "export"))
	{
		printf("export\n");
		return (0);
	}
	else if (!ft_strcmp(command[0], "exit"))
	{
		printf("exit\n");
		return (0);
	}
	else if (!ft_strcmp(command[0], "unset"))
	{
		printf("unset\n");
		return (0);
	}
	else if (!ft_strcmp(command[0], "cd"))
	{
		printf("cd\n");
		return (0);
	}
	else
		return (1);
}

void	act_child(t_deque_node *node, t_info *info)
{
	char	*bin_path;

	operate_pipe(info, node, 1);
	if (!check_run_builtin(node->command, info))
		printf("Builtin Function set\n");
	else
	{
		make_bin_path(info->env, node->command[0], &bin_path);
		if (execve(bin_path, node->command, info->env) == -1)
			printf("Child Error\n");
	}
	exit(1);
}

void	check_seperate(t_info *info, t_deque_node *temp_node)
{
	info->is_prev_pipe = info->is_pipe;
	if (temp_node->seperate && !ft_strcmp(temp_node->seperate, "|"))
		info->is_pipe = 1;
	else
		info->is_pipe = 0;
}

void	operate_pipe(t_info *info, t_deque_node *node, int flag)
{
	if (flag == 0 && info->is_pipe)
		pipe(node->pipe);
	else if (flag == 1)
	{
		if (info->is_pipe)
			dup2(node->pipe[1], STDOUT_FILENO);
		if (info->is_prev_pipe)
			dup2(node->prev_node->pipe[0], STDIN_FILENO);
	}
	else if (flag == 2)
	{
		if (info->is_pipe)
		{
			close(node->pipe[1]);
			if (node->next_node == &(info->cmd->tailer_node))
				close(node->pipe[0]);
		}
		if (info->is_prev_pipe)
			close(node->prev_node->pipe[0]);
	}
}
