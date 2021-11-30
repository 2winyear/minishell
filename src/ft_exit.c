#include "../include/minishell.h"

void	ft_exit(char **command, t_info *info)
{
	int	exit_num;
	int	idx;

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
	info->status = exit_num;
	printf("exit\n");
	exit(exit_num);
}
