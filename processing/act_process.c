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

int		check_redirection(t_deque_node *node)
{
	if (node->prev_node->seperate[0] == '>')
		return (0);
	return (1);
}

void	redirection(t_deque_node *node, t_info *info)
{
	int		fd;
	int		byte;
	char	buf[BUF_SIZE];

	fd = open(node->command[0], O_TRUNC | O_RDWR | O_CREAT, 00644);
	if (fd == -1)
	{
		printf("Open error\n");
		exit(1);
	}
	byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	while (byte > 0)
	{
		buf[byte] = '\0';
		write(fd, buf, byte);
		byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	}
	exit(0);
}

void	act_child(t_deque_node *node, t_info *info)
{
	char	*bin_path;

	operate_pipe(info, node, 1);
	printf("out\n");
	if (!check_run_builtin(node->command, info))
		printf("Builtin Function set\n");
	else if (!check_redirection(node))
	{
		printf("redirection\n");
		redirection(node, info);
	}
	else
	{
		printf("builtin\n");
		if (node->command[0][0] != '/')
			make_bin_path(info->env, node->command[0], &bin_path);
		else
			bin_path = node->command[0];
		if (execve(bin_path, node->command, info->env) == -1)
			printf("Child Error\n");
	}
	printf("out????\n");
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
