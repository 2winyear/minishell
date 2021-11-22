#include "../include/minishell.h"

int my_bind_esc(int count, int key)
{
	rl_done = 1;    // 이 변수가 0이 아니면 문자열이 끝난걸로 간주
	printf("\n");
	return (0);
}

char    *read_line(void)
{
    char    *str;

    rl_bind_key(SIGILL, my_bind_esc);   // 처리할 키(Ctrl+D) 바인딩
    str = readline("👍 ");   // 라인 읽어오기
    if (str)                // 공백 처리되면 NULL반환
    {
        if (strlen(str))
            add_history(str);   // 공백아닌 명령어만 히스토리에 저장
    }
    return (str);
}
