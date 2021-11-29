#include "../include/minishell.h"

void	run_single_cmd(t_info *info)
{
	if (check_run_builtin(info->cmd->header_node.next_node->command, info))
		info->cmd->current_element_count -= 1;
}

int	check_run_builtin(char **command, t_info *info)
{
	if (!ft_strcmp(command[0], "export"))
		ft_export(command, info);
	else if (!ft_strcmp(command[0], "exit"))
		ft_exit(command);
	else if (!ft_strcmp(command[0], "unset"))
	{
		if (!ft_unset(command, info))
			return (0);
	}
	else if (!ft_strcmp(command[0], "cd"))
	{
		if (!ft_cd(command, info))
			return (0);
	}
	else if (!ft_strcmp(command[0], "echo"))
		ft_echo(command, info);
	else
		return (0);
	return (1);
}

void	act_child(t_deque_node *node, t_info *info)
{
	char	*bin_path;

	operate_pipe(info->cmd, node, 1);
	if (check_run_builtin(node->command, info))
		exit(0);
	else if (check_run_redirection(node))
		printf("Redirection Function set\n");
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
	if (flag == 0 && node->spt_type > 0)
		pipe(node->pipe);
	else if (flag == 1)
	{
		if (node->spt_type > 0)
			dup2(node->pipe[1], STDOUT_FILENO);
		if (node->prev_node->spt_type > 0)
			dup2(node->prev_node->pipe[0], STDIN_FILENO);
	}
	else if (flag == 2)
	{
		if (node->spt_type > 0)
		{
			close(node->pipe[1]);
			if (node->next_node == &(cmd->tailer_node))
				close(node->pipe[0]);
		}
		if (node->prev_node->spt_type > 0)
			close(node->prev_node->pipe[0]);
	}
}