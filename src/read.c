#include "../include/minishell.h"

void	sig_handler(int signum)
{
	extern void	rl_replace_line(const char *text, int n);

	if (signum == SIGINT)
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
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*read_line(t_info *info)
{
	char		*str;
	char		*prompt;
	extern int	rl_catch_signals;

	init_signal();
	prompt = ft_strjoin(info->pwd, "  ▶ ");
	if (!prompt)
		exit(1);
	rl_catch_signals = 0;
	str = readline(prompt);
	free(prompt);
	if (!str)
	{
		printf("exit\n");
		exit(4);
	}
	else if (str)
	{
		if (strlen(str))
			add_history(str);
	}
	return (str);
}
