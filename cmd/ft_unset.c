#include "../include/minishell.h"

ft_unset(char *command, t_info *info)
{
	char	**edit_env;
	int		i;

	info->env_size =- 1;
	**edit_env = malloc(sizeof(char*) * info->env_size);
	i = -1;
	while (info->env[++i])
	{
		if (ft_strnstr(info->env[i], command, info->env_size))
		{
			i++;
		}
		edit_env[i] = info->env;
	}
	while ()
	{
		env=strdup(edit_env);
	}
}

int main(int argc, char **argv, char **env)
{
	char *command = "TEST";
	t_info *info;
	int i;

	i = 0;
	info = init_info(env);
	printf("env_size: %d\n", info->env_size);
	ft_unset(command, info);
	printf("env_size: %d\n", info->env_size);
	for (int i = 0; info->env[i]; i++)
		printf("declare -x %s\n", info->env[i]);
	return (0);
}