#include "../include/minishell.h"

void    display_logo(void)
{
    int     fd;
    int     bytes;
    char    buf[1025];

    // /Users/{USER_NAME}/Downloads/minishell/minishell/util/front_logo
    fd = open("/Users/byeukim/Downloads/minishell/util/front_logo",O_RDONLY);
    if (fd < 0)
        return ;
    bytes = read(fd, buf, 1024);
    buf[bytes] = '\0';
    if (bytes == -1)
    {
        close(fd);
        return ;
    }
    printf("%s", buf);
    close(fd);
}

void	*free_info(t_info *info)
{
	int	idx;

	idx = -1;
	if (info->cmd)
		delete_deque(&(info->cmd));
	if (info->env)
	{
		while (info->env[++idx])
		{
			free(info->env[idx]);
			info->env[idx] = NULL;
		}
		free(info->env);
		info->env = NULL;
	}
	if (info->pwd)
		free(info->pwd);
	free(info);
	info = NULL;
	return (NULL);
}

t_info	*init_info(char **env)
{
	t_info	*info;
	int		idx;
	int		i;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	for (i=0; env[i]; i++)
		;
	info->env = malloc(sizeof(char*) * i);
	for (i = 0; env[i]; i++)
		info->env[i] = ft_strdup(env[i]);
	info->env[i] = 0;
//	info->env = env;
	idx = -1;
	while (env[++idx])
	{
		if (!ft_strncmp(env[idx], "PWD=", 4))
		{
			info->pwd = ft_strdup(env[idx] + 4);
			if (!info->pwd)
				return (free_info(info));
		}
		if (!info->env[idx])
			return (free_info(info));
	}
	info->env_size = idx;
	info->is_pipe = 0;
	info->is_prev_pipe = 0;
	return (info);
}
