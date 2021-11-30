#include "../include/minishell.h"

int	is_flag(char *command)
{
	int	idx;

	idx = 0;
	if (command[idx] != '-')
		return (0);
	while (command[++idx])
	{
		if (command[idx] != 'n')
			return (0);
	}
	return (1);
}

void	print_echo(char *command)
{
	int	idx;

	idx = -1;
	while (command[++idx])
	{
		if (command[idx] != '\'')
			printf("%c", command[idx]);
	}
	printf(" ");
}

void	ft_echo(char **command)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (command[++idx])
	{
		if (!flag)
		{
			flag = is_flag(command[idx]);
			if (flag)
				continue ;
		}
		print_echo(command[idx]);
	}
	printf("\b");
	if (flag != 1)
		printf("\n");
}
