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
	return (1);
}

void	act_child(t_deque_node *node, t_info *info)
{
	char	*bin_path;

	operate_pipe(info->cmd, node, 1);
	if (!check_run_builtin(node->command, info))
		printf("Builtin Function set\n");
//	else if (!check_redirection(node))
//		redirection(node, info);
	else
	{
		if (node->command[0][0] != '/')
			make_bin_path(info->env, node->command[0], &bin_path);
		else
			bin_path = node->command[0];
		if (execve(bin_path, node->command, info->env) == -1)
			printf("Child Error\n");
	}
	exit(1);
}

void	operate_pipe(t_deque *cmd, t_deque_node *node, int flag)
{
	if (flag == 0 && node->spt_type == 1)
		pipe(node->pipe);
	else if (flag == 1)
	{
		if (node->spt_type == 1)
			dup2(node->pipe[1], STDOUT_FILENO);
		if (node->prev_node->spt_type == 1)
			dup2(node->prev_node->pipe[0], STDIN_FILENO);
	}
	else if (flag == 2)
	{
		if (node->spt_type == 1)
		{
			close(node->pipe[1]);
			if (node->next_node == &(cmd->tailer_node))
				close(node->pipe[0]);
		}
		if (node->prev_node->spt_type == 1)
			close(node->prev_node->pipe[0]);
	}
}
