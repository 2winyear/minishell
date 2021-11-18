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

// int ft_export(char **env, char  *command)
// {
//     int     idx;
//     int     i;
//     char    **line;
    
//     line = ft_split(command, ' ');
//     if (!line)
//         return (-1);
//     if (ft_strncmp(line[0], "export", ft_strlen("export")))
//         return (-1);
//     if (line[1] == NULL)
//     {
//         idx = -1;
//         while (env[++idx])
//         {
//             i = -1;
//             while (env[idx][++i])
//             {
//                 printf("%c", env[idx][i]);
//                 if (env[idx][i] == '=')
//                     printf("\"");
//             }
//             printf("\"\n");
//         }
//     }
//     return (1);
// }

// int main(int argc, char **argv, char **env)
// {
//     if (ft_export(env, argv[1]) == -1)
//         return (1);
//     return (0);
// }

char **resizing(char ***env, int size)
{
	int i;
	char **edit_env;

	edit_env = malloc(sizeof(size + 1));
	i = 0;
	while (env[i])
	{
		edit_env[i] = env[i];
		i++;
	}
	edit_env[size + i] = '\0';
	i = 0;
	while (env[i])
	{
		free(*env[i]);
	}
	free(*env);
	*env = NULL;
	return (edit_env);
}

void ft_export(char **env, char *command)
{
	char	**sorted_env;
	int		env_size;
	int		i = -1;

	//sort. test에서 복붙
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
	//////////////////////////////
	env_size = i;
	if (command == NULL)
	{
		sort_env(sorted_env, 0, i - 1);
		i = 0;
		while (env[i])
		{
			printf("%s", "declare -x ");
			printf("%s\n", sorted_env[i]);
		}
	}
	else
	{
		env = resizing(&env, env_size);

	}
}

int main(int argc, char **argv, char **env)
{
	char *command = "hell=HELLO_HELL";
	ft_export(env, command);

	return (0);
}