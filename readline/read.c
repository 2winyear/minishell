#include "../include/minishell.h"

int	my_bind_esc(int count, int key)
{
	rl_done = 1;
	printf("\n");
	return (0);
}

char	*read_line(void)
{
	char	*str;

	rl_bind_key(SIGILL, my_bind_esc);
	str = readline("👍 ");
	if (str)
	{
		if (strlen(str))
			add_history(str);
	}
	return (str);
}
