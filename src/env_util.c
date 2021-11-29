#include "../include/minishell.h"

void	*free_matrix(char ***matrix)
{
	int	idx;

	idx = -1;
	while ((*matrix)[++idx])
		free((*matrix)[idx]);
	free(*matrix);
	*matrix = NULL;
	return (NULL);
}

char	**env_dup(char **env, int flag, char *app_str)
{
	char	**edit_env;
	int		idx;

	idx = -1;
	while (env[++idx])
		;
	edit_env = malloc(sizeof(char *) * (idx + 1 + flag));
	if (!edit_env)
		return (NULL);
	idx = -1;
	while (env[++idx])
	{
		edit_env[idx] = ft_strdup(env[idx]);
		if (!edit_env[idx])
			return (free_matrix(&edit_env));
	}
	if (flag)
	{
		edit_env[idx] = ft_strdup(app_str);
		if (!edit_env[idx++])
			return (free_matrix(&edit_env));
	}
	edit_env[idx] = NULL;
	return (edit_env);
}

char	**find_bin_path(char **env)
{
	int		idx;
	char	**bin_path;

	idx = -1;
	while (env[++idx])
		if (!ft_strncmp(env[idx], "PATH=", 5))
			break ;
	bin_path = ft_split(env[idx] + 5, ':');
	if (!bin_path)
		return (NULL);
	return (bin_path);
}

char	*make_bin_path(char **env, char *cmd, char **path)
{
	DIR				*dir;
	struct dirent	*ent;
	int				idx;
	char			**bin_path;

	bin_path = find_bin_path(env);
	idx = -1;
	while (bin_path[++idx])
	{
		dir = opendir(bin_path[idx]);
		if (dir == NULL)
			return (free_matrix(&bin_path));
		ent = readdir(dir);
		while (ent != NULL)
		{
			if (!ft_strcmp(ent->d_name, cmd))
			{
				*path = ft_strjointri(bin_path[idx], "/", cmd);
				return (free_matrix(&bin_path));
			}
			ent = readdir(dir);
		}
	}
	return (free_matrix(&bin_path));
}
