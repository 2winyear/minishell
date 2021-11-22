#include "../include/minishell.h"

char	*make_bin_path(char **env, char *cmd)
{
	DIR		*dir;
	struct dirent *ent;
	int		idx;
	char	**bin_path;
	char	*path;

	idx = -1;
	while (env[++idx])
	{
		if (!ft_strncmp(env[idx], "PATH=", 5))
			break ;
	}
	bin_path = ft_split(env[idx] + 5, ':');
	idx = -1;
	while (bin_path[++idx])
	{
		dir = opendir(bin_path[idx]);
		if (dir == NULL)
			return (NULL);
		while ((ent = readdir(dir)) != NULL)
		{
			if (!ft_strcmp(ent->d_name, cmd))
			{
				path = ft_strjointri(bin_path[idx], "/", cmd);
				return (path);
			}
		}
	}
	return (NULL);
}
