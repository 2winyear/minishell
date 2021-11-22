#include "../include/minishell.h"

void	*free_env(char ***env)
{
	int	idx;

	idx = -1;
	while ((*env)[idx])
		free((*env)[idx]);
	free(*env);
	return (NULL);
}

char	**env_dup(char **env, int flag, char *app_str)
{
	char	**edit_env;
	int		idx;

	idx = -1;
	while (env[++idx])
		;
	edit_env = malloc(sizeof(char*) * (idx + flag));
	if (!edit_env)
		return (NULL);
	idx = -1;
	while (env[++idx])
	{
		edit_env[idx] = ft_strdup(env[idx]);
		if (!edit_env[idx])
			return(free_env(&edit_env));
	}
	if (!flag) // flag = 0 -> 추가 | 1 -> 복사
	{
		edit_env[idx] = ft_strdup(app_str);
		if (!edit_env[idx])
			return (free_env(&edit_env));
	}
	edit_env[idx + 1] = 0;
	return(edit_env);
}