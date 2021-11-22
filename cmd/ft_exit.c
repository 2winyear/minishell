#include "../include/minishell.h"

int ft_exit(char **command)
{
    int exit_num;
    int idx;

    exit_num = EXIT_FAILURE;
    if (command)
    {
        if (command[2] == NULL)
        {
            idx = -1;
            exit_num = 0;
            while (command[1][++idx])
            {
                if (!ft_isdigit(command[1][idx]))
                {
                    exit_num = 255;
                    break ;
                }
                exit_num = exit_num * 10 + (command[1][idx] - '0');
            }
        }
    }
    printf("%s\n", strerror(exit_num));
    exit(exit_num);
}

int main(void)
{
    char    *argv;
    char    **command;

    argv = "exit 15";
    command = ft_split(argv, ' ');
    if (!ft_strncmp(command[0], "exit", ft_strlen("exit")))
        ft_exit(command);
    return (0);
}
/*
int main(void)
{
    char    *error_message;

    printf("< error와 message 목록 >");
    for (errno = 0; errno < 108; errno++)
    {
        error_message = strerror(errno);
        printf("errno : %d\tmessage : %s\n", errno, error_message);
    }
    return (0);
}*/

/*
exit() 함수는 오퍼레이팅 시스템에 status 값과 제어를 둘 다 리턴합니다.
*/