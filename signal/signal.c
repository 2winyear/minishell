#include "../include/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		exit(SIGINT);
	return ;
}

void	init_signal(void)
{
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
