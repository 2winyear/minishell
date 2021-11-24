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

int	ft_cd(char **command, t_info *info)
{
	int		idx;
	char	**split_cmd;
	char	*cur_path;

	idx = -1;
	split_cmd = ft_split(command[1], '/');
	if (command[1][0] == '/')
		chdir("/");
	cur_path = getcwd(NULL, BUFSIZ);
	while (split_cmd[++idx])
	{
		printf("cur_path : %s\n", cur_path);
		if (!move_dir(split_cmd[idx], &cur_path))
		{
			free_matrix(&split_cmd);
			return (0);
		}
	}
	free(info->pwd);
	info->pwd = getcwd(NULL, BUFSIZ);
	return (1);
}

int main(int argc, char **argv, char **env)
{
	char *command[] = {(char *)"cd", (char *)"test"};
	char *command1[] = {(char *)"cd", (char *)".."};
	char *command2[] = {(char *)"cd", (char *)"/Users/seungyel/Downloads/minishell 2/minishell/"};
	t_info	*info;

	info = init_info(env);
	ft_cd(command, info);
	printf("pwd : %s\n", info->pwd);
	ft_cd(command1, info);
	printf("pwd : %s\n", info->pwd);
	ft_cd(command2, info);
	printf("pwd : %s\n", info->pwd);
}