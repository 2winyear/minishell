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

int	find_dollar(char *command, t_info *info)
{
	int		i;
	int		len;
	char	*temp;

	i = -1;
	temp = ft_strnstr(command, "$", 1);
	if (!temp)
		return (0);
	else if (temp[1] == '?')
	{
		printf("%d", info->status);
		find_dollar(temp + 1, info);
		return (1);
	}
	len = temp - command;
	while (++i < len)
		printf("%c", command[i]);
	i = -1;
	while (info->env[++i])
	{
		if (ft_strnstr(info->env[i], temp + 1, ft_strlen(temp + 1)) \
		 && info->env[i][ft_strlen(temp + 1)] == '=')
			printf("%s", info->env[i] + ft_strlen(temp + 1) + 1);
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

void	ft_echo(char **command, t_info *info)
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
		if (find_dollar(command[idx], info))
			;
		else
			print_echo(command[idx]);
	}
	printf("\b");
	if (flag != 1)
		printf("\n");
}
