#include "../include/minishell.h"

int	move_dir(char *cmd, char **cur_path)
{
	DIR *dir;
	struct dirent *ent;
	char *temp;

	dir = opendir(*cur_path);
	if (!dir)
		return (0);
	ent = readdir(dir);
	while (ent)
	{
		if (!ft_strcmp(ent->d_name, cmd))
		{
			temp = ft_strjointri(*cur_path, "/", cmd);
			chdir(temp);
			free(temp);
			*cur_path = getcwd(NULL, BUFSIZ);
			closedir(dir);
			return (1);
		}
		ent = readdir(dir);
	}
	return (0);
}

int	move_base(char **command, t_info *info)
{
	char	*tmp;

	if (command[1][0] == '/')
		chdir("/");
	else if (command[1][0] == '~')
	{
		chdir(info->home);
		return (1);
	}
	else if (command[1][0] == '-')
	{
		if (!info->oldpwd)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return (0);
		}
		tmp = ft_strjoin(info->home, info->oldpwd);
		if (!tmp)
			return (0);
		chdir(tmp);
		printf("%s\n", tmp);
		free(tmp);
		return (1);
	}
	return (1);
}

int	ft_cd(char **command, t_info *info)
{
	int		idx;
	char	**split_cmd;
	char	*cur_path;

	idx = -1;
	if (!move_base(command, info))
		return (0);
	split_cmd = ft_split(command[1], '/');
	cur_path = getcwd(NULL, BUFSIZ);
	info->oldpwd = cur_path;
	while (split_cmd[++idx])
	{
		if (split_cmd[idx][0] != '~' && split_cmd[idx][0] != '-'\
				&& !move_dir(split_cmd[idx], &cur_path))
		{
			free_matrix(&split_cmd);
			return (0);
		}
	}
	info->pwd = NULL;
	info->pwd = getcwd(NULL, BUFSIZ);
	return (1);
}
