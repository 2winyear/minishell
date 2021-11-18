#include "../include/minishell.h"

int     ft_env(char **env)
{
    int idx;

    idx = -1;
    while (env[++idx])
        printf("%s\n", env[++idx]);
    return (0);
}