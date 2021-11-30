#include "../include/minishell.h"

int		space_count(char *command)
{
	int		idx;
	int		count;
	int		flag;

	idx = -1;
	count = 1;
	flag = 0;
	while (command[++idx])
	{
		if (!flag && command[idx] == '"')
		{
			flag = 1;
			continue ;
		}
		else if (flag && command[idx] == '"')
		{
			flag = 0;
			continue ;
		}
		else if (flag)
			continue ;
		if (command[idx] == ' ')
			count += 1;
	}
	return (count);
}

char	*add_word(char **result, char word)
{
	char	*new;
	int		len;
	int		idx;

	if (!(*result))
		len = 0;
	else
		len = ft_strlen(*result);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	idx = 0;
	while ((*result) && (*result)[idx])
	{
		new[idx] = (*result)[idx];
		idx++;
	}
	new[idx] = word;
	new[idx + 1] = 0;
	free(*result);
	return (new);
}

char	*conv_dallor(char *result, char *command, int len, t_info *info)
{
	char	*env_element;
	char	*key;
	char	*temp;

	key = ft_strndup(command, len);
	env_element = find_env_value(info, key);
	if (env_element)
	{
		if (!result)
			result = env_element;
		else
		{
			temp = ft_strjoin(result, env_element);
			free(result);
			result = temp;
			if (env_element)
				free(env_element);
		}
	}
	else
		result = ft_strdup("");
	if (key)
		free(key);
	return (result);
}
