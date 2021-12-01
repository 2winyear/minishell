#include "../include/minishell.h"

int	check_flag(char *command)
{
	int	idx;

	idx = 0;
	if (command[0] != '-')
		return (1);
	while (command[++idx])
	{
		if (command[idx] != 'n')
			return (1);
	}
	return (0);
}

void	ft_echo(char **command)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (check_flag(command[idx + 1]) == 0)
	{	
		flag = 1;
		idx += 1;
	}
	while (command[++idx])
		printf("%s ", command[idx]);
	printf("\b");
	if (flag != 1)
		printf("\n");
}
