#include "../include/minishell.h"

int	execute_exit(void)
{
	printf("Process Error\n");
	exit(1);
}

int	execute(t_info *info)
{
	t_deque_node	*temp_node;
	pid_t			child_pid;
	int				status;

	if (info->cmd && info->cmd->current_element_count == 1)
		run_single_cmd(info);
	while (info->cmd && info->cmd->current_element_count)
	{
		temp_node = pop_front_deque(info->cmd);
		operate_pipe(info->cmd, temp_node, 0);
		child_pid = fork();
		if (child_pid == 0)
			act_child(temp_node, info);
		else if (child_pid > 0)
		{
			waitpid(child_pid, &status, 0);
			operate_pipe(info->cmd, temp_node, 2);
			info->status = status;
		}
		else
			execute_exit();
	}
	return (1);
}

void	inf_loop(t_info *info)
{
	char	*line;
	int		status;

	status = 42;
	while (status)
	{
		line = read_line(info);
		if (!parsing(line, info))
			exit(1);
		//display_deque(info->cmd);
		execute(info);
		delete_deque(&(info->cmd));
		if (line)
			free(line);
		line = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = init_info(env);
	display_logo(info);
	if (!info)
		return (FALSE);
	inf_loop(info);
	return (TRUE);
}
