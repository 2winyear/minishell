#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "minishell.h"

void	ft_swap(char **env, int i, int j)
{
	char	*temp;

	temp = env[i];
	env[i] = env[j];
	env[j] = temp;
}

void	sort_env(char **env, int start, int end)
{
	int pivot;
	int i;
	int j;
	
	if (start >= end)
		return ;
	pivot = start;
	i = pivot + 1;
	j = end;
	while(i <= j)
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

int main(int argc, char **argv, char **env)
{
	char	**sorted_env;
	int		i = -1;

	while (env[++i])
	{
		printf("%s\n", env[i]);
	}
	sorted_env = malloc(sizeof(char*) * i);
	i = 0;
	while (env[i])
	{
		sorted_env[i] = strdup(env[i]);
		i++;
	}
	printf("end point : %d\n", i);
	printf("\n------------- sort ------------\n");
	sort_env(sorted_env, 0, i - 1);

	i = -1;
	while (sorted_env[++i])
	{
		printf("%s\n", sorted_env[i]);
	}
	// i = -1;
	// while (sorted_env[++i])
	// {
	// 	printf("%s\n", sorted_env[i]);
	// }
	return (0);
}