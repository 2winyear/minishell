#include "include/minishell.h"

int		execute(t_info *info)
{
	t_deque_node	*temp_node;
	pid_t			child_pid;
	int				status;
	char			*bin_path;

	if (info->cmd && info->cmd->current_element_count == 1)
		run_single_cmd(info);
	while (info->cmd && info->cmd->current_element_count)
	{
		temp_node = pop_front_deque(info->cmd); // 커멘드 추출
		operate_pipe(info->cmd, temp_node, 0);
		child_pid = fork(); // 자식 생성
		if (child_pid == 0)
			act_child(temp_node, info); // 자식행동개시
		else if (child_pid > 0)
		{
			waitpid(child_pid, &status, 0); // 자식죽을때까지 기다림
			operate_pipe(info->cmd, temp_node, 2);
			info->status = status;
		}
		else // ERROR
		{
			printf("Process Error\n");
			exit(1);
		}
	}
	return (1);
}

void    inf_loop(t_info *info)
{
    char	*line;
    int		status;

    status = 42;				// 상태확인 인자
    while (status)
    {
        line = read_line(info);		// 커멘드 라인 읽기
		//printf("INPUT : %s\n", line);
		info->cmd = parsing(line);	// tokenizing
		//display_deque(info->cmd);
		execute(info);
	    delete_deque(&(info->cmd));
		if (line)
			free(line);         // line 사용 후 제거
		line = NULL;
		//while(42) ;
    }
}

int main(int argc, char **argv, char **env)
{
	t_info	*info;

    display_logo(); // 시작 로고 프린트
	info = init_info(env);
	if (!info)
		return (FALSE);
    inf_loop(info);     // 무한루프 시작
    return (TRUE);
}
