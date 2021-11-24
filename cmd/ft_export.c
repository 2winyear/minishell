#include "../include/minishell.h"

void	ft_swap(char **env, int i, int j)
{
	char	*temp;

	temp = env[i];
	env[i] = env[j];
	env[j] = temp;
}

void	sort_env(char **env, int start, int end)
{
	int	pivot;
	int	i;
	int	j;

	if (start >= end)
		return ;
	pivot = start;
	i = pivot + 1;
	j = end;
	while (i <= j)
	{
		while (i <= end && strcmp(env[i], env[pivot]) <= 0)
			i++;
		while (j > start && strcmp(env[j], env[pivot]) >= 0)
			j--;
		if (i > j)
			ft_swap(env, j, pivot);
		else
			ft_swap(env, i, j);
	}
	sort_env(env, start, j - 1);
	sort_env(env, j + 1, end);
}

char	**copy_or_resizing(char *command, t_info *info, int flag)
{
	int		i;
	char	**edit_env;

	edit_env = malloc(sizeof(char *) * (info->env_size));
	i = -1;
	while (info->env[++i])
		edit_env[i] = ft_strdup(info->env[i]);
	if (!flag)
	{
		edit_env[i] = 0;
		return (edit_env);
	}
	edit_env[i] = ft_strdup(command);
	edit_env[i + 1] = NULL;
	return (edit_env);
}

void	ft_export(char *command, t_info *info)
{
	char	**sorted_env;
	int		i;

	if (command == NULL)
	{
		sorted_env = copy_or_resizing(command, info, 0);
		sort_env(sorted_env, 0, i - 1);
		i = -1;
		while (info->env[++i])
		{
			printf("declare -x ");
			printf("%s\n", sorted_env[i]);
		}
	}
	else
	{
		info->env_size += 1;
		info->env = copy_or_resizing(command, info, 1);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*command = "TEST=test1";
	t_info	*info;
	int		i;

	i = 0;
	info = init_info(env);
	printf("env_size: %d\n", info->env_size);
	ft_export(command, info);
	printf("env_size: %d\n", info->env_size);
	for (int i = 0; info->env[i]; i++)
		printf("declare -x %s\n", info->env[i]);
	return (0);
}

/*
ft_export(char **env, char *command)
{
    if command == NULL
        env를 정렬하고
        while ()
            print
    else
        env의 길이 세고 = size
        env = resizing(&env, size);
        끝에 command 추가
        '\0' 추가
}

Exit Status
0 Successful completion.
>0 An error occurred.
*/