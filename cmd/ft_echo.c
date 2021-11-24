#include "../include/minishell.h"

int	is_flag(char *command)
{
	int	idx;

	idx = 0;
	if (command[idx] != '-')
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
	while (command[++idx])
	{
		if (!flag)
			flag = is_flag(command[idx]);
		if (flag == 1)
			printf("%s ", command[idx]);
	}
	printf("\b");
	if (flag == 1)
		printf("\n");
}
/*
0. cd
cd cmd   => cmd로 이동
cd ~     => home으로 이동
cd -     => oldpwd로 이동

1. echo $PWD

2. echo $? -> 종료상태
*/