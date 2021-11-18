#include "include/minishell.h"
/*
char    *execute(command_node *command)
{
    char    *argv;

    argv = NULL;
    argv = ft_echo(command, argv);
    argv = ft_cd(command, argv);
    argv = ft_pwd(command, argv);
    argv = ft_export(command, argv);
    argv = ft_unset(command, argv);
    argv = ft_env(command, argv);
    argv = ft_exit(command, argv);
    argv = ft_redirection(command, argv);
    return (argv);
}

int     interpret(command_node *commands)
{
    command_node    *command;
    char            *argv;
    
    while (commands)
    {
        if (commands->seperate == "<<")
            commands = change_order(commands, ">>");
        else if (commands->seperate == "<")
            commands = change_order(commands, ">");
        //command = split_line(commands->command, " ");
        //argv = execute(command);
        commands = commands->next;
    }
    
}*/

void    inf_loop(void)
{
    char	*line;
    deque	*cmd;
    int		status;

    status = 42;            // 상태확인 인자
    while (status)
    {
        line = read_line(); // 커멘드 라인 읽기
		printf("INPUT : %s\n", line);
		cmd = parsing(line);
        // 구조체 생성 초기화하는 함수
        // 자식프로세스 생성 함수
        // 커멘드 구분 함수
        // 리다이렉션 수행 함수
        display_deque(cmd);
	    delete_deque(cmd);
	    cmd = NULL;
        // commands = split_line(line);  // 구분자마다 토크나이징
        // status = interpret(commands);   // 토큰마다 해석, 실행
        free(line);         // line 사용 후 제거
		//while(42) ;
        // 링크드 리스트 제거(free)
    }
}

int main(void)
{
    init_signal();  // 시그널 초기화
    display_logo(); // 시작 로고 프린트
    inf_loop();     // 무한루프 시작
    return (TRUE);
}
