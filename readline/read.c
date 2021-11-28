#include "../include/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGILL)
	{
		printf("SIGILL\n");
	}
	else if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	init_signal(void)
{
	signal(4, (void *)sig_handler);
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*read_line(t_info *info)
{
	char	*str;
	char	*prompt;

	init_signal();
	prompt = ft_strjoin(info->pwd, "  ▶ ");
	if (!prompt)
		exit(1);
	rl_catch_signals = 0;
	str = readline(prompt);
	if (!str)
	{
		printf("exit");
		exit(4);
	}
	else if (str)
	{
		if (strlen(str))
			add_history(str);
	}
	free(prompt);
	return (str);
}
