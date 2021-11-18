#include "../include/minishell.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)   // Ctrl+C 처리
        exit(130);
    return;
}

void    init_signal(void)
{
    signal(SIGINT, (void*)sig_handler); // Ctrl+C 처리
    signal(SIGQUIT, SIG_IGN);           // Ctrl+'\' 무시
}