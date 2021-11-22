#include "../include/minishell.h"

int ft_export(char **env, char  *command)
{
    int     idx;
    int     i;
    char    **line;
    
    line = ft_split(command, ' ');
    if (!line)
        return (-1);
    if (ft_strncmp(line[0], "export", ft_strlen("export")))
        return (-1);
    if (line[1] == NULL)
    {
        idx = -1;
        while (env[++idx])
        {
            i = -1;
            while (env[idx][++i])
            {
                printf("%c", env[idx][i]);
                if (env[idx][i] == '=')
                    printf("\"");
            }
            printf("\"\n");
        }
    }
    return (1);
}

int main(int argc, char **argv, char **env)
{
    if (ft_export(env, argv[1]) == -1)
        return (1);
    return (0);
}