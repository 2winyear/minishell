#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
    char *arg[] = {"ls", (char *)0};
    printf("Running ls with execve\n");
    /* 첫 번째 인수가 경로 이름이고 명령라인 인수는 인수들의 배열. 환경 변수 넘겨 줌 */
    execve("/bin/ls", arg, env);
    printf("execve failed to run ls\n");
    exit(0);
}
