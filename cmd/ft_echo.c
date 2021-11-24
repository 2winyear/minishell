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
}

// int	main(int argc, char **argv)
// {
// 	char	*line;
// 	char	**command;	
// 	line = argv[1];
// 	command = ft_split(line, ' ');
// 	if (!ft_strncmp(command[0], "echo", ft_strlen(command[0])))
// 		ft_echo(command);
// 	return(0);
// }

/*
0	Successful completion.
>0	An error occurred.
*/