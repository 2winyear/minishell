#include "../include/minishell.h"

int	ft_env(char **env)
{
	int	idx;

	idx = -1;
	while (env[++idx])
		printf("%s\n", env[++idx]);
	return (0);
}
// 0	The env command completed successfully.
// 1-125	An error occurred in the env command.
// 126	The command specified by the Command parameter was found, but could not be invoked.
// 127	The command specified by the Command parameter was not found.