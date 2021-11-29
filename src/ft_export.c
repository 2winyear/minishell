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

	edit_env = malloc(sizeof(char *) * (info->env_size + flag + 1));
	if (!edit_env)
		return (NULL);
	i = -1;
	while (info->env[++i])
		edit_env[i] = ft_strdup(info->env[i]);
	if (!flag)
	{
		edit_env[i] = NULL;
		return (edit_env);
	}
	edit_env[i] = ft_strdup(command);
	edit_env[i + 1] = NULL;
	return (edit_env);
}

void	ft_export(char **command, t_info *info)
{
	char	**sorted_env;
	int		i;

	if (command[1] == NULL)
	{
		sorted_env = copy_or_resizing(command[1], info, 0);
		sort_env(sorted_env, 0, info->env_size - 1);
		i = -1;
		while (info->env[++i])
		{
			printf("declare -x ");
			printf("%s\n", sorted_env[i]);
		}
		free_matrix(&sorted_env);
	}
	else
	{
		info->env_size += 1;
		info->env = copy_or_resizing(command[1], info, 1);
	}
}
